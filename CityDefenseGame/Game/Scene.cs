using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CityDefense.Engine;
namespace CityDefense.Game
{
    class Scene : IScene
    {
        Image backGround;
        int houseOffset = 100;
        int planeAddTime = 10;
        int planeTimer;
        int maxPlanes = 7;
        public List<House> houses = new List<House>();
        public List<Plane> planes = new List<Plane>();
        public List<Bomb> bombs = new List<Bomb>();
        public List<Effect> effects = new List<Effect>();
        public Scene()
        {
            
            Resources.InitializationResources();
            backGround = Resources.GetFrame("Back");
            for(int i = 0; i< Render.Resolution.X / houseOffset; i++)
                houses.Add(new House(25+i* houseOffset, 280,70,70));
            Sound.Play("Siren");
        }
        public void DrawBack(Graphics g, int x, int y) => g.DrawImage(backGround, 0, 0, x, y);
        public void DrawObjects(Graphics g)
        {            
            if((planeTimer -= Time.deltaTime) <= 0 && planes.Count < maxPlanes)
            {
                planeTimer = planeAddTime*1000;
                planes.Add(new Plane(0, 70, 70, 40, 7, 2));
                bombs.Add(new Bomb(40, 40, 7, 2, this));
            }                
            List<IGameObject> objects = new List<IGameObject>();
            objects.AddRange(planes);
            objects.AddRange(houses);
            objects.AddRange(bombs);
            objects.AddRange(effects);
            foreach (var i in objects)
                i.Draw(g);
            CheckBreak();
        }
        public void UseEffect(Vector pos) => effects.Add(new Effect(pos, 60, 60, this));
        public void BreakBomb(int x, int y)
        {
            foreach (var i in bombs)
                if (i.Colision(x, y))
                    i.Break();
        }
        public void CheckBreak()
        {
                
            foreach(var bomb in bombs)
            {
                int breakCount = 0;
                foreach (var i in houses)
                {
                    if (i.IsBreak)
                    {
                        breakCount++;
                        continue;
                    }
                    if (i.Colision(bomb.Position.X + bomb.Size.X / 2, bomb.Position.Y + bomb.Size.Y / 2))
                    {
                        bomb.Break();
                        i.Break();
                    }
                   

                }
                
                if (breakCount == houses.Count)
                    GameOver.isGameOver = true;
            }                
        }
    }
}
