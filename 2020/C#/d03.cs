using System;
namespace _2020
{
    class d03
    {
        public static void solve(){
            Console.WriteLine("Day 03");
            Int64 result = 0;
            string data = System.IO.File.ReadAllText(@"../input/03.txt");
            char[,] matrix = new char[data.Split('\n').Length, data.Split('\n')[0].Length-1];

            for (int y=0; y < data.Split('\n').Length; y++){
                for (int x=0; x < data.Split('\n')[0].Length-1; x++){
                    matrix[y, x] = data.Split('\n')[y][x];
                }
            }
            // Part1
            result = transite(1, 3, matrix);
            Console.WriteLine($"Part 1: {result}");
            
            // Part2
            long a = transite(1,1, matrix);
            long b = transite(1,3, matrix);
            long c = transite(1,5, matrix);
            long d = transite(1,7, matrix);
            long e = transite(2,1, matrix);
            Console.WriteLine($"Part 2: {a*b*c*d*e}");
        }

        static long transite(int down, int right, char[,] matrix){
            int y = 0; int x = 0; long result = 0;
            while (y < matrix.GetLength(0)-1){
                y = y + down;
                x = (x + right) % matrix.GetLength(1);
                if (matrix[y,x] == '#'){
                    result++;
                }
            } 
            return result;
        }
    }
}