using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CityDefense.Game
{
    class Plane : Transform, IGameObject
    {
        int speed;        
        public Plane(int x, int y, int sx, int sy, int speed, int offsetSpeed)
        {
            Random random = new Random();
            SetPosition(new Vector(x, y + random.Next(-sy,sy)));
            SetSize(new Vector(sx, sy));            
            this.speed = speed + random.Next(-offsetSpeed,offsetSpeed);            
        }
        public void Draw(Graphics g)
        {
            AddPosition(new Vector(speed,0));
            if (Position.X < Render.Resolution.X - Size.X)
                speed *= -1;
            if (Position.X > 0)
                speed *= -1;
            g.DrawImage(speed > 0? Resources.GetFrame("PlaneRight"): Resources.GetFrame("PlaneLeft"),
            Position.X, Position.Y, Size.X, Size.Y);
        }
    }
}
