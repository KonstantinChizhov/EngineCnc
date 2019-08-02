
#pragma once

namespace EngineCnc
{
template <class StepPinsT, class DirPinsT, class EnablePinsT, class DelayT, unsigned MinPulseDelay>
class StepDirStepper
{
public:
    typedef typename StepPinsT::DataT DataT;
    static constexpr int Count = StepPinsT::Length;
    static constexpr DataT Mask = (1 << Count) - 1;
    static DelayT delay;

    static void Init()
    {
        StepPinsT::SetConfiguration(StepPinsT::Out);
        DirPinsT::SetConfiguration(DirPinsT::Out);
        EnablePinsT::SetConfiguration(EnablePinsT::Out);
    }

    static void StepPulseBegin(DataT value)
    {
        StepPinsT::Write(value);
        delay.Start();
    }
    static void StepPulseEnd()
    {
        delay.Wait(MinPulseDelay);
        StepPinsT::Write(0);
    }
    static void SetDirection(DataT value)
    {
        DirPinsT::Write(value);
    }
    static void Enable()
    {
        EnablePinsT::Write(Mask);
    }
    static void Disable()
    {
        EnablePinsT::Write(0);
    }
};

template <class StepPinsT, class DirPinsT, class EnablePinsT, class DelayT, unsigned MinPulseDelay>
DelayT StepDirStepper<StepPinsT, DirPinsT, EnablePinsT, DelayT, MinPulseDelay>::delay {0};

} // namespace EngineCnc