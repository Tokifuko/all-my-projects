using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

using MathWorks.MATLAB.NET.Utility;
using MathWorks.MATLAB.NET.Arrays;
using MathWorks.MATLAB.NET.WebFigures;
using MathWorks.MATLAB.NET.WebFigures.RenderEngine;

namespace GUI_muscule
{
    public partial class Grafics : Form
    {
        int i = 0;
        myMatlabLib.MTLClass mylObj = new myMatlabLib.MTLClass();
        MWNumericArray input = null;
        MWNumericArray output = null;
        MWArray[] result = null;
        MWArray MTLfigHandler = null;
        public Grafics()
        {
            InitializeComponent();
            MTLfigHandler = mylObj.GetFigHandle();
        }
        /*
        public static void PlolExemple()
        {
                try
                {
                    const int numPoints = 10;  // Number of points to plot

                    // Allocate native array for plot values
                    double[,] plotValues = new double[2, numPoints];

                    // Plot 5x vs x^2
                    for (int x = 1; x <= numPoints; x++)
                    {
                        plotValues[0, x - 1] = x * 5;
                        plotValues[1, x - 1] = x * x;
                    }

                    // Create a new plotter object
                    PlotComp.PlotComp plotter = new PlotComp.PlotComp();

                    // Plot the two sets of values - Note the ability to cast the native array to a MATLAB numeric array
                    plotter.drawgraph((MWNumericArray)plotValues);

                   // Console.ReadLine();  // Wait for user to exit application
                }

                catch (Exception ex)
                {
                    System.Windows.Forms.MessageBox.Show(ex.Message);
                   // Console.WriteLine("Error: {0}", exception);
                   // Console.ReadLine();  // Wait for user to exit application
                }
        }*/
        public byte[] getByteArrayFromDeployedComponent(int r)
        {
            MWArray width = 500;
            MWArray height = 500;
            MWArray rotation = 10*r;
            MWArray elevation = 30;
            MWArray imageFormat = "png";
            MWNumericArray result =  (MWNumericArray)mylObj.figToImStream_fibonachi2D(
            MTLfigHandler,
            height,
            width,
            elevation,
            rotation,
            imageFormat);
            return (byte[])result.ToVector(MWArrayComponent.Real);
        }
        public Image Get_StreamImage(int r)
        {
            Image outputImageAsImage = null;
            try
            {
                byte[] byteArray = getByteArrayFromDeployedComponent(r);
                MemoryStream ms = new MemoryStream(byteArray, 0,
                byteArray.Length);
                ms.Write(byteArray, 0, byteArray.Length);
                outputImageAsImage= Image.FromStream(ms, true);
            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message);
            }
            return outputImageAsImage;
        }
        public Image Get_WebImage(int r)
        {
            Image outputImageAsImage=null;
            try
            {
                WebFigure figure = new WebFigure(mylObj.webfigure_fibonachi2D());
                WebFigureRenderer renderer = new WebFigureRenderer();
                WebFigureRenderParameters param =new WebFigureRenderParameters(figure);
                param.Rotation = 10*r;
                param.Elevation = 30;
                param.Width = 500;
                param.Height = 500;
                outputImageAsImage =renderer.RenderToImage(param);
            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message);
            }
            return outputImageAsImage;
        }
        public void ShowMatlabChart()
        {
            try
            {
                mylObj = new myMatlabLib.MTLClass();
                mylObj.fibonachi2D();
            }
            catch(Exception ex)//обработка исключения 
            {
              System.Windows.Forms.MessageBox.Show(ex.Message);
                i++;;
                label1.Text = "Ээксэпшн" + i.ToString();
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //ShowMatlabChart();
            //pictureBox1.Image = Get_WebImage(i++);
            pictureBox1.Image = Get_StreamImage(i++);
            //PlolExemple();
        }
    }
    /*
    WebFigure figure =
new WebFigure(deployment.getWebFigure());
WebFigureRenderer renderer =
new WebFigureRenderer();
//Creates a parameter object that can be changed
// to represent a specific WebFigure and its orientation.
//If you dont set any values it uses the defaults for that
// figure (what they were when the figure was created in M).
WebFigureRenderParameters param =
new WebFigureRenderParameters(figure);
param.Rotation = 30;
param.Elevation = 30;
8-378 Web Deployment of Figures and Images
param.Width = 500;
param.Height = 500;
//If you need a byte array that can be streamed out
// of a web page you can use this:
byte[] outputImageAsBytes =
renderer.RenderToEncodedBytes(param);
//If you need a .NET Image (can't be used on the web)
// you can use this code:
Image outputImageAsImage =
renderer.RenderToImage(param);
     * */
}
