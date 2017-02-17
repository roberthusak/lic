using System;

namespace Basic
{
    public class Point
    {
        public Point(int x, int y, int z)
        {
            this.X = x;
            this.Y = y;
            this.z = z;
        }

        public int X { get; set; }

        public int Y { get; set; }

        public int z;
    }

    public class References
    {
        public static void InstanceTest()
        {
            var point = new Point(1, 2, 3);

            point.X = 2 * point.Y;
            point.z = point.X + point.z;
        }
    }
}