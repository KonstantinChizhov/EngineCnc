
#pragma once

namespace EngineCnc
{
template <class MinEndstopPins, class MaxEndStopPins>
class PinEndstop
{
public:
    typedef typename MinEndstopPins::DataT DataT;
    static constexpr int Count = MinEndstopPins::Length;
    static constexpr DataT Mask = (1 << Count) - 1;
    static void Init()
    {
        MinEndstopPins::SetConfiguration(MinEndstopPins::In);
        MinEndstopPins::SetPullUp(MinEndstopPins::PullUp);
        MaxEndStopPins::SetConfiguration(MaxEndStopPins::In);
        MaxEndStopPins::SetPullUp(MaxEndStopPins::PullUp);
    }

    static DataT ReadMin() { return MinEndstopPins::PinRead(); }
    static DataT ReadMax() { return MaxEndStopPins::PinRead(); }
};

} // namespace EngineCnc