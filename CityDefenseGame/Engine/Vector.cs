namespace CityDefense
{
    class Vector
    {
        int x;
        int y;
        public Vector() //Инициализация
        {
            this.x = 0;
            this.y = 0;
        }
        public Vector(int x, int y) //Перегрузка инициализации
        {
            this.x = x;
            this.y = y;
        }
        public int X => x; //Получаем координаты
        public int Y => y;

        public static Vector operator +(Vector a, Vector b) => new Vector(a.x+b.x,a.y+b.y);
        public static Vector operator -(Vector a, Vector b) => new Vector(a.x - b.x, a.y - b.y);

    }
}
