using System;
using System.Linq;
using System.Text;



namespace GUI_muscule.PointSource
{
    public delegate void FigClose();
    public interface IPointRecever<T>
    {
        void AddPoint(T tPoint);
        FigClose pCloseCallback { set; get; }
    }
}
