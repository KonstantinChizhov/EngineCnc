
#pragma once

namespace EngineCnc
{
template <class StepPins, class DirPins, class EnablePins>
class StepDirStepper
{
public:
    typedef typename StepPins::DataT DataT;
    static constexpr int Count = StepPins::Length;
    static constexpr DataT Mask = (1 << Count) - 1;

    static void StepPulseBegin(DataT value)
    {
        StepPins::Write(value);
    }
    static void StepPulseEnd()
    {
        StepPins::Write(0);
    }
    static void SetDirection(DataT value)
    {
        DirPins::Write(value);
    }
    static void Enable()
    {
        EnablePins::Write(Mask);
    }
    static void Disable()
    {
        EnablePins::Write(0);
    }
};

} // namespace EngineCnc