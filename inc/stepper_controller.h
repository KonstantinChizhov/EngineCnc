
#pragma once

#include <algorithm>
#include <array>
#include <containers/span.h>

namespace EngineCnc
{

template <class T>
using span = Mcucpp::Containers::span<T>;

template <class Stepper, class Endstop, class CoordT>
class StepperController
{
public:
    typedef typename Stepper::DataT DataT;

protected:
    std::array<CoordT, Stepper::Count> _numerator;
    std::array<CoordT, Stepper::Count> _error;
    std::array<CoordT, Stepper::Count> _position;
    std::array<int_fast8_t, Stepper::Count> _direction;
    CoordT _denominator;
    uint32_t _stepCount;
    DataT _directionPositiveMask;
    DataT _directionNegativeMask;

public:
    StepperController()
        : _denominator{0},
          _stepCount{0},
          _directionPositiveMask{0},
          _directionNegativeMask{0}
    {
    }

    void Init()
    {
        Endstop::Init();
        Stepper::Init();
    }

    void Enable()
    {
        Stepper::Enable();
    }

    void Disable()
    {
        Stepper::Disable();
        _stepCount = 0;
        _denominator = 0;
        _directionPositiveMask = 0;
        _directionNegativeMask = 0;
    }

    uint32_t GetStepCount()
    {
        return _stepCount;
    }

    void SetPosition(int indx, CoordT value)
    {
        if (indx < Stepper::Count)
        {
            _position[indx] = value;
        }
    }

    CoordT GetPosition(int indx)
    {
        return indx < Stepper::Count ? _position[indx] : 0;
    }

    void MoveTo(span<CoordT> targetPosition)
    {
        _stepCount = 0;
        _denominator = *std::max_element(std::begin(targetPosition), std::end(targetPosition));
        DataT directionPositiveMask = 0;
        DataT directionNegativeMask = 0;

        DataT mask = 1;
        for (uint_fast8_t i = 0; i < Stepper::Count; i++)
        {
            //_error[i] = 0;
            if (_position[i] > targetPosition[i])
            {
                _numerator[i] = _position[i] - targetPosition[i];
                _direction[i] = -1;
                directionNegativeMask |= mask;
            }
            else
            {
                _numerator[i] = targetPosition[i] - _position[i];
                _direction[i] = 1;
                directionPositiveMask |= mask;
            }
            mask <<= 1;
        }
        _directionPositiveMask = directionPositiveMask;
        _directionNegativeMask = directionNegativeMask;
    }

    void Step()
    {
        DataT combinedPulseMask = 0;
        DataT singlePulseMask = 1;
        // use Bresenham algorithm to calculate steps
        for (uint_fast8_t i = 0; i <= Stepper::Count; i++)
        {
            if (_error[i] > _denominator)
            {
                combinedPulseMask |= singlePulseMask;
            }
            singlePulseMask <<= 1;
        }

        // apply min endstops limitations
        combinedPulseMask &= ~(_directionNegativeMask & Endstop::ReadMin());

        // apply max endstops limitations
        combinedPulseMask &= ~(_directionPositiveMask & Endstop::ReadMax());

        Stepper::StepPulseBegin(combinedPulseMask);

        singlePulseMask = 1;
        for (uint_fast8_t i = 0; i <= Stepper::Count; i++)
        {
            if (combinedPulseMask & singlePulseMask)
            {
                _error[i] -= _denominator;
                _position[i] += _direction[i];
            }
            _error[i] += _numerator[i];
            singlePulseMask <<= 1;
        }

        Stepper::StepPulseEnd();
    }
};

} // namespace EngineCnc