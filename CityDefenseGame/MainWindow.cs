using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CityDefense.Game;
using CityDefense.Engine;

namespace CityDefense
{
    public partial class MainWindow : Form
    {
        Scene scene;
        public MainWindow()
        {
            InitializeComponent();            
            
            Render.SetResolution(renderBox.Width, renderBox.Height);
            Render.SetScene(scene = new Scene());
            
            Time.SetInterval(Frame.Interval);
            Frame.Tick += new System.EventHandler(Time.Frame_Tick);
        }

        private void Frame_Tick(object sender, EventArgs e)
        {
            renderBox.BackgroundImage = Render.DrawFrame();
            Frame.Enabled = !GameOver.isGameOver;
        }

        private void renderBox_MouseDown(object sender, MouseEventArgs e)
        {
            scene.BreakBomb(e.X, e.Y);
        }

        private void renderBox_Click(object sender, EventArgs e)
        {

        }
    }
}
