using System;
using System.IO;

namespace _2020
{
    class d02
    {
        public static void solve(){
            Console.WriteLine("Day 02");
            string file = File.ReadAllText(@"../input/02.txt");
            int count = 0; int valid = 0;

            foreach (string line in file.Split('\n')){
                int low = Convert.ToInt32(line.Split()[0].Split('-')[0]);
                int hig = Convert.ToInt32(line.Split()[0].Split('-')[1]);
                char c = Convert.ToChar(line.Split()[1][^2]);
                string psw = line.Split()[2];

                // Modo per contare  la ripetizione di un sigolo carattere
                int repeat = psw.Split(c).Length - 1;
                // Part 1
                if (low <= repeat && repeat <= hig){
                    count++;
                }
                // Part 2
                if ((psw[low - 1] == c) ^ (psw[hig - 1] == c)){
                    valid++;
                }
            }
            Console.WriteLine($"Part 1: {count}");
            Console.WriteLine($"Part 2: {valid}");
        }
    }
}