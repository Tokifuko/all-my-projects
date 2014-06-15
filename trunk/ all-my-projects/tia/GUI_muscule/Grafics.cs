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
using GUI_muscule.MatLabChats;

using MathWorks.MATLAB.NET.Utility;
using MathWorks.MATLAB.NET.Arrays;
//using MathWorks.MATLAB.NET.WebFigures;
//using MathWorks.MATLAB.NET.WebFigures.RenderEngine;

namespace GUI_muscule
{
    public partial class Grafics : Form
    {
        MatLabAdapter myMTL ;
        int i = 0;
        public Grafics()
        {
            InitializeComponent();
            myMTL = new MatLabAdapter();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            
            double d;
            for (i = 0; i < 50; i++)
            {
                d = i * i;
                myMTL.AddNewPoint((int)d);
            }
          //  myMTL.Repaint();
             
        }

        private void button2_Click(object sender, EventArgs e)
        {
            myMTL.Init();
        }

        private void button3_Click(object sender, EventArgs e)
        {
         /*   int[] iMass=new int [50];
            for (i = 0; i < 50; i++)
            {
                iMass[i] = i * i; 
            }
            myMTL.AddNewPoint(iMass);
            myMTL.Repaint();*/
        }
    }
}
