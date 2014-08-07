using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_muscule.PacketManager
{
    public enum SmartDataBufState
    {
        EMPTY = 0,
        ACTIVE = 1,
        READY = 2
    }
    public class SmartDataBuf
    {
        public SmartDataBuf() { }
        public DataPack_t DataPack = new DataPack_t();
        private byte[] buf = new byte[Constants.POCKET_LENGTH];
        private SmartDataBufState bStatus = 0;
        private byte bCounter = 0;
        public void ClearPocket()
        {
            bStatus = SmartDataBufState.EMPTY;
            bCounter = 0;
        }
        public SmartDataBufState GetStatus() { return bStatus; }
        public void AddNewByte(byte b)
        {
            // если первый байт совпадает с началом префикса, то активирум пакет
            if (bCounter == 0)
            {
                if (b != Constants.POCKET_HI_PREFIX) return;
                bStatus = SmartDataBufState.ACTIVE;
            }
            buf[bCounter] = b;

            // проверяем вторую часть префикса
            if (bCounter == 1)
            {
                // если перфикс не совпадает - метим пакет как пустой
                if (b != Constants.POCKET_LO_PREFIX)
                {
                    ClearPocket();
                    return;
                }
            }
            //пакет готов когда все байты получены
            bCounter++;
            if (bCounter == Constants.POCKET_LENGTH)
            {
                DataPack = new DataPack_t(buf);
                if (DataPack.CRC16 == DataPack.CalcCRC())
                {
                    bStatus = SmartDataBufState.READY;
                    //DataPack.RxTime = DateTime.Now;
                }
                else ClearPocket();
            }
        }// AddNewByte
    }//struct SmartDataBuf
}
