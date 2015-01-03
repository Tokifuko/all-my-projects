/*
* MATLAB Compiler: 5.1 (R2014a)
* Date: Fri Jan 02 21:54:46 2015
* Arguments: "-B" "macro_default" "-W"
* "dotnet:MatLabSaveVectorLib,MTLSaveVector,0.0,private" "-T" "link:lib" "-d"
* "C:\all-my-projects\tia\Matlab\MatLabSaveVectorLib\for_testing" "-v"
* "C:\all-my-projects\tia\Matlab\ClearVectorStorage.m"
* "C:\all-my-projects\tia\Matlab\SaveVectorStorage.m"
* "C:\all-my-projects\tia\Matlab\StoreVector.m"
* "class{MTLSaveVector:C:\all-my-projects\tia\Matlab\ClearVectorStorage.m,C:\all-my-projec
* ts\tia\Matlab\SaveVectorStorage.m,C:\all-my-projects\tia\Matlab\StoreVector.m}" 
*/
using System;
using System.Reflection;
using System.IO;
using MathWorks.MATLAB.NET.Arrays;
using MathWorks.MATLAB.NET.Utility;

#if SHARED
[assembly: System.Reflection.AssemblyKeyFile(@"")]
#endif

namespace MatLabSaveVectorLib
{

  /// <summary>
  /// The MTLSaveVector class provides a CLS compliant, MWArray interface to the MATLAB
  /// functions contained in the files:
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\ClearVectorStorage.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\SaveVectorStorage.m
  /// <newpara></newpara>
  /// C:\all-my-projects\tia\Matlab\StoreVector.m
  /// <newpara></newpara>
  /// deployprint.m
  /// <newpara></newpara>
  /// printdlg.m
  /// </summary>
  /// <remarks>
  /// @Version 0.0
  /// </remarks>
  public class MTLSaveVector : IDisposable
  {
    #region Constructors

    /// <summary internal= "true">
    /// The static constructor instantiates and initializes the MATLAB Compiler Runtime
    /// instance.
    /// </summary>
    static MTLSaveVector()
    {
      if (MWMCR.MCRAppInitialized)
      {
        try
        {
          Assembly assembly= Assembly.GetExecutingAssembly();

          string ctfFilePath= assembly.Location;

          int lastDelimiter= ctfFilePath.LastIndexOf(@"\");

          ctfFilePath= ctfFilePath.Remove(lastDelimiter, (ctfFilePath.Length - lastDelimiter));

          string ctfFileName = "MatLabSaveVectorLib.ctf";

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
    /// Constructs a new instance of the MTLSaveVector class.
    /// </summary>
    public MTLSaveVector()
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
    ~MTLSaveVector()
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
    /// Provides a void output, 0-input MWArrayinterface to the ClearVectorStorage MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Отчищает глобальные накопители
    /// </remarks>
    ///
    public void ClearVectorStorage()
    {
      mcr.EvaluateFunction(0, "ClearVectorStorage", new MWArray[]{});
    }


    /// <summary>
    /// Provides the standard 0-input MWArray interface to the ClearVectorStorage MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// Отчищает глобальные накопители
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] ClearVectorStorage(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "ClearVectorStorage", new MWArray[]{});
    }


    /// <summary>
    /// Provides a single output, 0-input MWArrayinterface to the SaveVectorStorage
    /// MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray SaveVectorStorage()
    {
      return mcr.EvaluateFunction("SaveVectorStorage", new MWArray[]{});
    }


    /// <summary>
    /// Provides a single output, 1-input MWArrayinterface to the SaveVectorStorage
    /// MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <param name="path">Input argument #1</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray SaveVectorStorage(MWArray path)
    {
      return mcr.EvaluateFunction("SaveVectorStorage", path);
    }


    /// <summary>
    /// Provides a single output, 2-input MWArrayinterface to the SaveVectorStorage
    /// MATLAB function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <param name="path">Input argument #1</param>
    /// <param name="filename">Input argument #2</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray SaveVectorStorage(MWArray path, MWArray filename)
    {
      return mcr.EvaluateFunction("SaveVectorStorage", path, filename);
    }


    /// <summary>
    /// Provides the standard 0-input MWArray interface to the SaveVectorStorage MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] SaveVectorStorage(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "SaveVectorStorage", new MWArray[]{});
    }


    /// <summary>
    /// Provides the standard 1-input MWArray interface to the SaveVectorStorage MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="path">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] SaveVectorStorage(int numArgsOut, MWArray path)
    {
      return mcr.EvaluateFunction(numArgsOut, "SaveVectorStorage", path);
    }


    /// <summary>
    /// Provides the standard 2-input MWArray interface to the SaveVectorStorage MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="path">Input argument #1</param>
    /// <param name="filename">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] SaveVectorStorage(int numArgsOut, MWArray path, MWArray filename)
    {
      return mcr.EvaluateFunction(numArgsOut, "SaveVectorStorage", path, filename);
    }


    /// <summary>
    /// Provides an interface for the SaveVectorStorage function in which the input and
    /// output
    /// arguments are specified as an array of MWArrays.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// M-Documentation:
    /// проверяем правильность пути
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of MWArray output arguments</param>
    /// <param name= "argsIn">Array of MWArray input arguments</param>
    ///
    public void SaveVectorStorage(int numArgsOut, ref MWArray[] argsOut, MWArray[] argsIn)
    {
      mcr.EvaluateFunction("SaveVectorStorage", numArgsOut, ref argsOut, argsIn);
    }


    /// <summary>
    /// Provides a single output, 0-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector()
    {
      return mcr.EvaluateFunction("StoreVector", new MWArray[]{});
    }


    /// <summary>
    /// Provides a single output, 1-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force)
    {
      return mcr.EvaluateFunction("StoreVector", Force);
    }


    /// <summary>
    /// Provides a single output, 2-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press);
    }


    /// <summary>
    /// Provides a single output, 3-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press, MWArray Speed)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press, Speed);
    }


    /// <summary>
    /// Provides a single output, 4-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press, MWArray Speed, MWArray 
                         Length)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press, Speed, Length);
    }


    /// <summary>
    /// Provides a single output, 5-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press, MWArray Speed, MWArray 
                         Length, MWArray ValveInPower)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press, Speed, Length, ValveInPower);
    }


    /// <summary>
    /// Provides a single output, 6-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <param name="ValveOutPower">Input argument #6</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press, MWArray Speed, MWArray 
                         Length, MWArray ValveInPower, MWArray ValveOutPower)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press, Speed, Length, ValveInPower, ValveOutPower);
    }


    /// <summary>
    /// Provides a single output, 7-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <param name="ValveOutPower">Input argument #6</param>
    /// <param name="ValveInCount">Input argument #7</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press, MWArray Speed, MWArray 
                         Length, MWArray ValveInPower, MWArray ValveOutPower, MWArray 
                         ValveInCount)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press, Speed, Length, ValveInPower, ValveOutPower, ValveInCount);
    }


    /// <summary>
    /// Provides a single output, 8-input MWArrayinterface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <param name="ValveOutPower">Input argument #6</param>
    /// <param name="ValveInCount">Input argument #7</param>
    /// <param name="ValveOutCount">Input argument #8</param>
    /// <returns>An MWArray containing the first output argument.</returns>
    ///
    public MWArray StoreVector(MWArray Force, MWArray Press, MWArray Speed, MWArray 
                         Length, MWArray ValveInPower, MWArray ValveOutPower, MWArray 
                         ValveInCount, MWArray ValveOutCount)
    {
      return mcr.EvaluateFunction("StoreVector", Force, Press, Speed, Length, ValveInPower, ValveOutPower, ValveInCount, ValveOutCount);
    }


    /// <summary>
    /// Provides the standard 0-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", new MWArray[]{});
    }


    /// <summary>
    /// Provides the standard 1-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force);
    }


    /// <summary>
    /// Provides the standard 2-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press);
    }


    /// <summary>
    /// Provides the standard 3-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press, MWArray 
                           Speed)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press, Speed);
    }


    /// <summary>
    /// Provides the standard 4-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press, MWArray 
                           Speed, MWArray Length)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press, Speed, Length);
    }


    /// <summary>
    /// Provides the standard 5-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press, MWArray 
                           Speed, MWArray Length, MWArray ValveInPower)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press, Speed, Length, ValveInPower);
    }


    /// <summary>
    /// Provides the standard 6-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <param name="ValveOutPower">Input argument #6</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press, MWArray 
                           Speed, MWArray Length, MWArray ValveInPower, MWArray 
                           ValveOutPower)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press, Speed, Length, ValveInPower, ValveOutPower);
    }


    /// <summary>
    /// Provides the standard 7-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <param name="ValveOutPower">Input argument #6</param>
    /// <param name="ValveInCount">Input argument #7</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press, MWArray 
                           Speed, MWArray Length, MWArray ValveInPower, MWArray 
                           ValveOutPower, MWArray ValveInCount)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press, Speed, Length, ValveInPower, ValveOutPower, ValveInCount);
    }


    /// <summary>
    /// Provides the standard 8-input MWArray interface to the StoreVector MATLAB
    /// function.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return.</param>
    /// <param name="Force">Input argument #1</param>
    /// <param name="Press">Input argument #2</param>
    /// <param name="Speed">Input argument #3</param>
    /// <param name="Length">Input argument #4</param>
    /// <param name="ValveInPower">Input argument #5</param>
    /// <param name="ValveOutPower">Input argument #6</param>
    /// <param name="ValveInCount">Input argument #7</param>
    /// <param name="ValveOutCount">Input argument #8</param>
    /// <returns>An Array of length "numArgsOut" containing the output
    /// arguments.</returns>
    ///
    public MWArray[] StoreVector(int numArgsOut, MWArray Force, MWArray Press, MWArray 
                           Speed, MWArray Length, MWArray ValveInPower, MWArray 
                           ValveOutPower, MWArray ValveInCount, MWArray ValveOutCount)
    {
      return mcr.EvaluateFunction(numArgsOut, "StoreVector", Force, Press, Speed, Length, ValveInPower, ValveOutPower, ValveInCount, ValveOutCount);
    }


    /// <summary>
    /// Provides an interface for the StoreVector function in which the input and output
    /// arguments are specified as an array of MWArrays.
    /// </summary>
    /// <remarks>
    /// This method will allocate and return by reference the output argument
    /// array.<newpara></newpara>
    /// </remarks>
    /// <param name="numArgsOut">The number of output arguments to return</param>
    /// <param name= "argsOut">Array of MWArray output arguments</param>
    /// <param name= "argsIn">Array of MWArray input arguments</param>
    ///
    public void StoreVector(int numArgsOut, ref MWArray[] argsOut, MWArray[] argsIn)
    {
      mcr.EvaluateFunction("StoreVector", numArgsOut, ref argsOut, argsIn);
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
