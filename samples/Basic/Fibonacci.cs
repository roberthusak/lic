using System;

namespace Basic
{
    public static class Fibonacci
    {
        public static int FibSimple_0()
        {
            return 0;
        }

        public static int FibSimple_1()
        {
            return 1;
        }

        public static int FibSimple_2()
        {
            return 0 + 1;
        }

        public static int FibSimple_3()
        {
            int fib0 = 0;
            int fib1 = 1;
            int fib2 = fib0 + fib1;
            return fib1 + fib2;
        }

        public static int Fib_5()
        {
            int n = 5;

            if (n == 0)
            {
                return 0;
            }
            else if (n == 1)
            {
                return 1;
            }

            int minus2 = 0;
            int minus1 = 1;
            int current = -1;
            for (int i = 2; i <= n; i++)
            {
                current = minus2 + minus1;
                minus2 = minus1;
                minus1 = current;
            }

            return current;
        }

        public static int Fib_10()
        {
            int n = 10;

            if (n == 0)
            {
                return 0;
            }
            else if (n == 1)
            {
                return 1;
            }

            int minus2 = 0;
            int minus1 = 1;
            int current = -1;
            for (int i = 2; i <= n; i++)
            {
                current = minus2 + minus1;
                minus2 = minus1;
                minus1 = current;
            }

            return current;
        }

        public static int Fib_15()
        {
            int n = 15;

            if (n == 0)
            {
                return 0;
            }
            else if (n == 1)
            {
                return 1;
            }

            int minus2 = 0;
            int minus1 = 1;
            int current = -1;
            for (int i = 2; i <= n; i++)
            {
                current = minus2 + minus1;
                minus2 = minus1;
                minus1 = current;
            }

            return current;
        }

        public static int Fib_21()
        {
            int n = 21;

            if (n == 0)
            {
                return 0;
            }
            else if (n == 1)
            {
                return 1;
            }

            int minus2 = 0;
            int minus1 = 1;
            int current = -1;
            for (int i = 2; i <= n; i++)
            {
                current = minus2 + minus1;
                minus2 = minus1;
                minus1 = current;
            }

            return current;
        }
    }
}
