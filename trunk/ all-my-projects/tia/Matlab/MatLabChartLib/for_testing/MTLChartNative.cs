/*
* MATLAB Compiler: 5.1 (R2014a)
* Date: Sat Jan 03 15:23:45 2015
* Arguments: "-B" "macro_default" "-W" "dotnet:MatLabChartLib,MTLChart,4.0,private" "-T"
* "link:lib" "-d" "C:\all-my-projects\tia\Matlab\MatLabChartLib\for_testing" "-v"
* "C:\all-my-projects\tia\Matlab\GetAxesHandle.m"
* "C:\all-my-projects\tia\Matlab\GetFigHandle.m"
* "C:\all-my-projects\tia\Matlab\PlotArray.m"
* "C:\all-my-projects\tia\Matlab\PlotArray3D.m"
* "C:\all-my-projects\tia\Matlab\PlotSpectr.m"
* "C:\all-my-projects\tia\Matlab\SetObjProp.m"
* "C:\all-my-projects\tia\Matlab\SplitFigure.m"
* "class{MTLChart:C:\all-my-projects\tia\Matlab\GetAxesHandle.m,C:\all-my-projects\tia\Mat
* lab\GetFigHandle.m,C:\all-my-projects\tia\Matlab\PlotArray.m,C:\all-my-projects\tia\Matl
* ab\PlotArray3D.m,C:\all-my-projects\tia\Matlab\PlotSpectr.m,C:\all-my-projects\tia\Matla
* b\SetObjProp.m,C:\all-my-projects\tia\Matlab\SplitFigure.m}" "-a"
* "C:\all-my-projects\tia\Matlab\PolyfitnTools\polyfitn.m" "-a"
* "C:\all-my-projects\tia\Matlab\PolyfitnTools\polyvaln.m" 
*/
using System;
using System.Reflection;
using System.IO;
using MathWorks.MATLAB.NET.Arrays;
using MathWorks.MATLAB.NET.Utility;

#if SHARED
[assembly: System.Reflection.AssemblyKeyFile(@"")]
#endif

namespace MatLabChartLibNative
{

  /// <summary>
  /// The MTLChart class provides a CLS compliant, Object (native) interface to the
  /// MATLAB functions contained in the files:
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\GetAxesHandle.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\GetFigHandle.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\PlotArray.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\PlotArray3D.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\PlotSpectr.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\SetObjProp.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\SplitFigure.m
  /// <newpara></newpara>
  /// deployprint.m
  /// <newpara></newpara>
  /// printdlg.m
  /// </summary>
  /// <remarks>
  /// @Version 4.0
  /// </remarks>
  public class MTLChart : IDisposable
  {
    #region Constructors

    /// <summary internal= "true">
    /// The static constructor instantiates and initializes the MATLAB Compiler Runtime
    /// instance.
    /// </summary>
    static MTLChart()
    {
      if (MWMCR.MCRAppInitialized)
      {
        try
        {
          Assembly assembly= Assembly.GetExecutingAssembly();

          string ctfFilePath= assembly.Location;

          int lastDelimiter= ctfFilePath.LastIndexOf(@"\");

          ctfFilePath= ctfFilePath.Remove(lastDelimiter, (ctfFilePath.Length - lastDelimiter));

          string ctfFileName = "MatLabChartLib.ctf";

          Stream embeddedCtfStream = null;

          String[] resourceStrings = assembly.GetManifestResourceNames();

          foreach (String name in resourceStrings)
          {
            if (name.Contains(ctfFileName))
            {
              embeddedCtfStream = assembly.GetManifestResourceStream(name);
              break;
            }
          }
          mcr= new MWMCR("",
                         ctfFilePath, embeddedCtfStream, true);
        }
        catch(Exception ex)
        {
          ex_ = new Exception("MWArray assembly failed to be initialized", ex);
        }
      }
      else
      {
        ex_ = new ApplicationException("MWArray assembly could not be initialized");
      }
    }


    /// <summary>
    /// Constructs a new instance of the MTLChart class.
    /// </summary>
    public MTLChart()
    {
      if(ex_ != null)
      {
        throw ex_;
      }
    }


    #endregion Constructors

    #region Finalize

    /// <summary internal= "true">
    /// Class destructor called by the CLR garbage collector.
    /// </summary>
    ~MTLChart()
    {
      Dispose(false);
    }


    /// <summary>
    /// Frees the native resources associated with this object
    /// </summary>
    public void Dispose()
    {
      Dispose(true);

      GC.SuppressFinalize(this);
    }


    /// <summary internal= "true">
    /// Internal dispose function
    /// </summary>
    protected virtual void Dispose(bool disposing)
    {
      if (!disposed)
      {
        disposed= true;

        if (disposing)
        {
          // Free managed resources;
        }

        // Free native resources
      }
    }


    #endregion Finalize

    #region Methods

    /// <summary>
    /// Provides a single output, 0-input Objectinterface to the GetAxesHandle MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Возвращает указатель на оси
    /// </remarks>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object GetAxesHandle()
    {
      return mcr.EvaluateFunction("GetAxesHandle", new Object[]{});
    }


    /// <summary>
    /// Provides a single output, 1-input Objectinterface to the GetAxesHandle MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Возвращает указатель на оси
    /// </remarks>
    /// <param name="hFig">Input argument #1</param>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object GetAxesHandle(Object hFig)
    {
      return mcr.EvaluateFunction("GetAxesHandle", hFig);
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the GetAxesHandle MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Возвращает указатель на оси
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] GetAxesHandle(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "GetAxesHandle", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 1-input Object interface to the GetAxesHandle MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Возвращает указатель на оси
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hFig">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] GetAxesHandle(int numArgsOut, Object hFig)
    {
      return mcr.EvaluateFunction(numArgsOut, "GetAxesHandle", hFig);
    }


    /// <summary>
    /// Provides an interface for the GetAxesHandle function in which the input and
    /// output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// M-Documentation:
    /// Возвращает указатель на оси
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("GetAxesHandle", 1, 1, 0)]
    protected void GetAxesHandle(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("GetAxesHandle", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }
    /// <summary>
    /// Provides a single output, 0-input Objectinterface to the GetFigHandle MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// global  globalFigHandler ;
    /// globalFigHandler= figure('PaperSize',[20.98 29.68]);
    /// hFig=globalFigHandler;
    /// </remarks>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object GetFigHandle()
    {
      return mcr.EvaluateFunction("GetFigHandle", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the GetFigHandle MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// global  globalFigHandler ;
    /// globalFigHandler= figure('PaperSize',[20.98 29.68]);
    /// hFig=globalFigHandler;
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] GetFigHandle(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "GetFigHandle", new Object[]{});
    }


    /// <summary>
    /// Provides an interface for the GetFigHandle function in which the input and output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// M-Documentation:
    /// global  globalFigHandler ;
    /// globalFigHandler= figure('PaperSize',[20.98 29.68]);
    /// hFig=globalFigHandler;
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("GetFigHandle", 0, 1, 0)]
    protected void GetFigHandle(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("GetFigHandle", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }
    /// <summary>
    /// Provides a void output, 0-input Objectinterface to the PlotArray MATLAB function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    ///
    public void PlotArray()
    {
      mcr.EvaluateFunction(0, "PlotArray", new Object[]{});
    }


    /// <summary>
    /// Provides a void output, 1-input Objectinterface to the PlotArray MATLAB function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    ///
    public void PlotArray(Object hAxes)
    {
      mcr.EvaluateFunction(0, "PlotArray", hAxes);
    }


    /// <summary>
    /// Provides a void output, 2-input Objectinterface to the PlotArray MATLAB function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="points">Input argument #2</param>
    ///
    public void PlotArray(Object hAxes, Object points)
    {
      mcr.EvaluateFunction(0, "PlotArray", hAxes, points);
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the PlotArray MATLAB function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 1-input Object interface to the PlotArray MATLAB function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray(int numArgsOut, Object hAxes)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray", hAxes);
    }


    /// <summary>
    /// Provides the standard 2-input Object interface to the PlotArray MATLAB function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="points">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray(int numArgsOut, Object hAxes, Object points)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray", hAxes, points);
    }


    /// <summary>
    /// Provides an interface for the PlotArray function in which the input and output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("PlotArray", 2, 0, 0)]
    protected void PlotArray(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("PlotArray", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }
    /// <summary>
    /// Provides a void output, 0-input Objectinterface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    ///
    public void PlotArray3D()
    {
      mcr.EvaluateFunction(0, "PlotArray3D", new Object[]{});
    }


    /// <summary>
    /// Provides a void output, 1-input Objectinterface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    ///
    public void PlotArray3D(Object hAxes)
    {
      mcr.EvaluateFunction(0, "PlotArray3D", hAxes);
    }


    /// <summary>
    /// Provides a void output, 2-input Objectinterface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="X">Input argument #2</param>
    ///
    public void PlotArray3D(Object hAxes, Object X)
    {
      mcr.EvaluateFunction(0, "PlotArray3D", hAxes, X);
    }


    /// <summary>
    /// Provides a void output, 3-input Objectinterface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="X">Input argument #2</param>
    /// <param name="Y">Input argument #3</param>
    ///
    public void PlotArray3D(Object hAxes, Object X, Object Y)
    {
      mcr.EvaluateFunction(0, "PlotArray3D", hAxes, X, Y);
    }


    /// <summary>
    /// Provides a void output, 4-input Objectinterface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="X">Input argument #2</param>
    /// <param name="Y">Input argument #3</param>
    /// <param name="Z">Input argument #4</param>
    ///
    public void PlotArray3D(Object hAxes, Object X, Object Y, Object Z)
    {
      mcr.EvaluateFunction(0, "PlotArray3D", hAxes, X, Y, Z);
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray3D(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray3D", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 1-input Object interface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray3D(int numArgsOut, Object hAxes)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray3D", hAxes);
    }


    /// <summary>
    /// Provides the standard 2-input Object interface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="X">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray3D(int numArgsOut, Object hAxes, Object X)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray3D", hAxes, X);
    }


    /// <summary>
    /// Provides the standard 3-input Object interface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="X">Input argument #2</param>
    /// <param name="Y">Input argument #3</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray3D(int numArgsOut, Object hAxes, Object X, Object Y)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray3D", hAxes, X, Y);
    }


    /// <summary>
    /// Provides the standard 4-input Object interface to the PlotArray3D MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="X">Input argument #2</param>
    /// <param name="Y">Input argument #3</param>
    /// <param name="Z">Input argument #4</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotArray3D(int numArgsOut, Object hAxes, Object X, Object Y, Object 
                          Z)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotArray3D", hAxes, X, Y, Z);
    }


    /// <summary>
    /// Provides an interface for the PlotArray3D function in which the input and output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// M-Documentation:
    /// Invalid or deleted object.
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("PlotArray3D", 4, 0, 0)]
    protected void PlotArray3D(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("PlotArray3D", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }
    /// <summary>
    /// Provides a void output, 0-input Objectinterface to the PlotSpectr MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    ///
    public void PlotSpectr()
    {
      mcr.EvaluateFunction(0, "PlotSpectr", new Object[]{});
    }


    /// <summary>
    /// Provides a void output, 1-input Objectinterface to the PlotSpectr MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    ///
    public void PlotSpectr(Object hAxes)
    {
      mcr.EvaluateFunction(0, "PlotSpectr", hAxes);
    }


    /// <summary>
    /// Provides a void output, 2-input Objectinterface to the PlotSpectr MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="Fd">Input argument #2</param>
    ///
    public void PlotSpectr(Object hAxes, Object Fd)
    {
      mcr.EvaluateFunction(0, "PlotSpectr", hAxes, Fd);
    }


    /// <summary>
    /// Provides a void output, 3-input Objectinterface to the PlotSpectr MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="Fd">Input argument #2</param>
    /// <param name="points">Input argument #3</param>
    ///
    public void PlotSpectr(Object hAxes, Object Fd, Object points)
    {
      mcr.EvaluateFunction(0, "PlotSpectr", hAxes, Fd, points);
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the PlotSpectr MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotSpectr(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotSpectr", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 1-input Object interface to the PlotSpectr MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotSpectr(int numArgsOut, Object hAxes)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotSpectr", hAxes);
    }


    /// <summary>
    /// Provides the standard 2-input Object interface to the PlotSpectr MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="Fd">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotSpectr(int numArgsOut, Object hAxes, Object Fd)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotSpectr", hAxes, Fd);
    }


    /// <summary>
    /// Provides the standard 3-input Object interface to the PlotSpectr MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hAxes">Input argument #1</param>
    /// <param name="Fd">Input argument #2</param>
    /// <param name="points">Input argument #3</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] PlotSpectr(int numArgsOut, Object hAxes, Object Fd, Object points)
    {
      return mcr.EvaluateFunction(numArgsOut, "PlotSpectr", hAxes, Fd, points);
    }


    /// <summary>
    /// Provides an interface for the PlotSpectr function in which the input and output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// M-Documentation:
    /// Спектральное представление сигнала
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("PlotSpectr", 3, 0, 0)]
    protected void PlotSpectr(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("PlotSpectr", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }
    /// <summary>
    /// Provides a void output, 0-input Objectinterface to the SetObjProp MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    ///
    public void SetObjProp()
    {
      mcr.EvaluateFunction(0, "SetObjProp", new Object[]{});
    }


    /// <summary>
    /// Provides a void output, 1-input Objectinterface to the SetObjProp MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="hHandler">Input argument #1</param>
    ///
    public void SetObjProp(Object hHandler)
    {
      mcr.EvaluateFunction(0, "SetObjProp", hHandler);
    }


    /// <summary>
    /// Provides a void output, 2-input Objectinterface to the SetObjProp MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="hHandler">Input argument #1</param>
    /// <param name="sPropName">Input argument #2</param>
    ///
    public void SetObjProp(Object hHandler, Object sPropName)
    {
      mcr.EvaluateFunction(0, "SetObjProp", hHandler, sPropName);
    }


    /// <summary>
    /// Provides a void output, 3-input Objectinterface to the SetObjProp MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="hHandler">Input argument #1</param>
    /// <param name="sPropName">Input argument #2</param>
    /// <param name="vValue">Input argument #3</param>
    ///
    public void SetObjProp(Object hHandler, Object sPropName, Object vValue)
    {
      mcr.EvaluateFunction(0, "SetObjProp", hHandler, sPropName, vValue);
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the SetObjProp MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SetObjProp(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "SetObjProp", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 1-input Object interface to the SetObjProp MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hHandler">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SetObjProp(int numArgsOut, Object hHandler)
    {
      return mcr.EvaluateFunction(numArgsOut, "SetObjProp", hHandler);
    }


    /// <summary>
    /// Provides the standard 2-input Object interface to the SetObjProp MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hHandler">Input argument #1</param>
    /// <param name="sPropName">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SetObjProp(int numArgsOut, Object hHandler, Object sPropName)
    {
      return mcr.EvaluateFunction(numArgsOut, "SetObjProp", hHandler, sPropName);
    }


    /// <summary>
    /// Provides the standard 3-input Object interface to the SetObjProp MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hHandler">Input argument #1</param>
    /// <param name="sPropName">Input argument #2</param>
    /// <param name="vValue">Input argument #3</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SetObjProp(int numArgsOut, Object hHandler, Object sPropName, Object 
                         vValue)
    {
      return mcr.EvaluateFunction(numArgsOut, "SetObjProp", hHandler, sPropName, vValue);
    }


    /// <summary>
    /// Provides an interface for the SetObjProp function in which the input and output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// M-Documentation:
    /// tx=text('String',vValue); 
    /// set(hHandler,sPropName,tx);
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("SetObjProp", 3, 0, 0)]
    protected void SetObjProp(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("SetObjProp", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }
    /// <summary>
    /// Provides a single output, 0-input Objectinterface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object SplitFigure()
    {
      return mcr.EvaluateFunction("SplitFigure", new Object[]{});
    }


    /// <summary>
    /// Provides a single output, 1-input Objectinterface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="hFig">Input argument #1</param>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object SplitFigure(Object hFig)
    {
      return mcr.EvaluateFunction("SplitFigure", hFig);
    }


    /// <summary>
    /// Provides a single output, 2-input Objectinterface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="hFig">Input argument #1</param>
    /// <param name="m">Input argument #2</param>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object SplitFigure(Object hFig, Object m)
    {
      return mcr.EvaluateFunction("SplitFigure", hFig, m);
    }


    /// <summary>
    /// Provides a single output, 3-input Objectinterface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="hFig">Input argument #1</param>
    /// <param name="m">Input argument #2</param>
    /// <param name="n">Input argument #3</param>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object SplitFigure(Object hFig, Object m, Object n)
    {
      return mcr.EvaluateFunction("SplitFigure", hFig, m, n);
    }


    /// <summary>
    /// Provides a single output, 4-input Objectinterface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="hFig">Input argument #1</param>
    /// <param name="m">Input argument #2</param>
    /// <param name="n">Input argument #3</param>
    /// <param name="p">Input argument #4</param>
    /// <returns>An Object containing the first output argument.</returns>
    ///
    public Object SplitFigure(Object hFig, Object m, Object n, Object p)
    {
      return mcr.EvaluateFunction("SplitFigure", hFig, m, n, p);
    }


    /// <summary>
    /// Provides the standard 0-input Object interface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SplitFigure(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "SplitFigure", new Object[]{});
    }


    /// <summary>
    /// Provides the standard 1-input Object interface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hFig">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SplitFigure(int numArgsOut, Object hFig)
    {
      return mcr.EvaluateFunction(numArgsOut, "SplitFigure", hFig);
    }


    /// <summary>
    /// Provides the standard 2-input Object interface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hFig">Input argument #1</param>
    /// <param name="m">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SplitFigure(int numArgsOut, Object hFig, Object m)
    {
      return mcr.EvaluateFunction(numArgsOut, "SplitFigure", hFig, m);
    }


    /// <summary>
    /// Provides the standard 3-input Object interface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hFig">Input argument #1</param>
    /// <param name="m">Input argument #2</param>
    /// <param name="n">Input argument #3</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SplitFigure(int numArgsOut, Object hFig, Object m, Object n)
    {
      return mcr.EvaluateFunction(numArgsOut, "SplitFigure", hFig, m, n);
    }


    /// <summary>
    /// Provides the standard 4-input Object interface to the SplitFigure MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="hFig">Input argument #1</param>
    /// <param name="m">Input argument #2</param>
    /// <param name="n">Input argument #3</param>
    /// <param name="p">Input argument #4</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public Object[] SplitFigure(int numArgsOut, Object hFig, Object m, Object n, Object p)
    {
      return mcr.EvaluateFunction(numArgsOut, "SplitFigure", hFig, m, n, p);
    }


    /// <summary>
    /// Provides an interface for the SplitFigure function in which the input and output
    /// arguments are specified as an array of Objects.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of Object output arguments</param>
    /// <param name= "argsIn">Array of Object input arguments</param>
    /// <param name= "varArgsIn">Array of Object representing variable input
    /// arguments</param>
    ///
    [MATLABSignature("SplitFigure", 4, 1, 0)]
    protected void SplitFigure(int numArgsOut, ref Object[] argsOut, Object[] argsIn, params Object[] varArgsIn)
    {
        mcr.EvaluateFunctionForTypeSafeCall("SplitFigure", numArgsOut, ref argsOut, argsIn, varArgsIn);
    }

    /// <summary>
    /// This method will cause a MATLAB figure window to behave as a modal dialog box.
    /// The method will not return until all the figure windows associated with this
    /// component have been closed.
    /// </summary>
    /// <remarks>
    /// An application should only call this method when required to keep the
    /// MATLAB figure window from disappearing.  Other techniques, such as calling
    /// Console.ReadLine() from the application should be considered where
    /// possible.</remarks>
    ///
    public void WaitForFiguresToDie()
    {
      mcr.WaitForFiguresToDie();
    }



    #endregion Methods

    #region Class Members

    private static MWMCR mcr= null;

    private static Exception ex_= null;

    private bool disposed= false;

    #endregion Class Members
  }
}
