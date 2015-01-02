using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Printing;
using System.Threading.Tasks;
using WindowsFormsApplication4;
using NSubstitute;
using NUnit.Framework;



namespace WindowsFormsApplication4.Tests
{
    [TestFixture()]
    public class Form1Tests
    {
        Form1 myForm = new Form1();
       /* [Test()]
        
        public void getPaperSizeTest()
        {
            
            Bitmap  testImage= new Bitmap(800,100);
            PaperSize myPaper= myForm.getPaperSize(testImage, 80);
            double testRatio=(double) testImage.Height/ (double) testImage.Width;
            double paperRatio=myPaper.Height/myPaper.Width;
            if (testRatio == 0) Assert.Fail("testRatio  = " + testRatio.ToString());
            if (paperRatio == 0) Assert.Fail("paperRatio  = " + paperRatio.ToString());
            Assert.AreEqual((int)testRatio, (int)paperRatio);
        }
        */
        [Test()]
        public void mmToInch_and_inchToMm_test()
        {
            Assert.AreEqual(1000, myForm.inchToMm( myForm.mmToInch(1000)));
        }

        [Test()]
        public void PixToInchTest()
        {
            Assert.AreEqual(100, myForm.PixToInch(200));
        }
    }
}
