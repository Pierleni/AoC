using System;
using System.Collections.Generic;
using System.Linq;

namespace _2020
{
    class d05
    {
        public static void solve(){
            Console.WriteLine("Day 05");
            string data = System.IO.File.ReadAllText(@"../input/05.txt");
            var seats = new List<double>();
            // Part 1
            foreach (string line in data.Split('\n')){
                string nLine = line.Replace('F', '0')
                    .Replace('B', '1')
                    .Replace('L', '0')
                    .Replace('R', '1');
                
                double colum = Convert.ToInt32(nLine[0..7], 2);
                double row = Convert.ToInt32(nLine[7..10], 2);
                seats.Add((colum * 8) + row);
            }
            Console.WriteLine($"Part 1: {seats.Max()}");
            // Part 2
            seats.Sort();
            for (int i=0; i<seats.Count; i++){
                if ((i + 45) != seats[i]){                   
                    Console.WriteLine($"Part 2: {(seats[i]-1)}");
                    break;
                    
                }
            }
        }
    }
}