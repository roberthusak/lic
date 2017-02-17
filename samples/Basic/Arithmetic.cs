using System;

namespace Basic
{
    public class Arithmetic
    {
        public static int AddSimple()
        {
            int a = 1;
            int b = 10;

            int c = a + b;

            return c;
        }

        public static int Add(int a, int b)
        {
            return a + b;
        }

        public static void AddTest()
        {
            int x = 10;
            int y = 20;

            int w = Add(x, y);
        }

        public static int Subtract(int a, int b)
        {
            return a - b;
        }

        public static MyStruct AddStruct(MyStruct a, MyStruct b)
        {
            var result = new MyStruct()
            {
                X = a.X + b.X,
                Y = a.Y + b.Y
            };

            var other = new MyStruct(1, 2);

            return result;
        }

        public static int PassByRef(int x, ref int y, out int z)
        {
            y = -x;
            z = x + y;

            return y + z;
        }

        public static void PassByRefTest()
        {
            int a = 10;
            int b = 20;
            int c = 30;

            int d = PassByRef(a, ref b, out c);
        }
    }

    
    public struct MyStruct
    {
        public MyStruct(int x, int y)
        {
            this.X = x;
            this.Y = y;
        }

        public int X { get; set; }

        public int Y { get; set; }
    }
}
