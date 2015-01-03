using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_muscule.Valve
{
    public class DoubleVaveRandom
    {
        ValveDriver vdIn, vdOut;
        Random myRandom = new Random();
        byte bPowRangeMax = 255;
        byte bPowRangeMin = 0;
        byte bCountRangeMax = 255;
        byte bCountRangeMin = 0;
        int iDelayRangeMax = 2000; // 2 сек
        int iDelayRangeMin = 0;
        public DoubleVaveRandom(ValveDriver ValveIn, ValveDriver ValveOut)
        {
            vdIn = ValveIn; vdOut = ValveOut;
        }
        public void SetPowRange(byte bMax,byte bMin)
        {
            bPowRangeMax = bMax; bPowRangeMin = bMin;
        }
        public void SetCountRange(byte bMax,byte bMin)
        {
            bCountRangeMax = bMax; bCountRangeMin = bMin;
        }
        public void SetDelayRange(int iMax, int iMin)
        {
            iDelayRangeMax = iMax; iDelayRangeMin = iMin;
        }

        public int DelayElapsed()
        {
            byte bPow,bCount;
            bPow = (byte)myRandom.Next(bPowRangeMin, bPowRangeMax);
            bCount = (byte)myRandom.Next(bCountRangeMin, bCountRangeMax);
            double i = myRandom.NextDouble();
            if (i<0.5)// определяем на какой капан подавать команду
            {
                vdOut.Close();
                vdIn.Open(bPow, bCount);
            }
            else
            {
                vdIn.Close();
                vdOut.Open(bPow, bCount);
            }
            return myRandom.Next(iDelayRangeMin,iDelayRangeMax);
        }

    }
}
