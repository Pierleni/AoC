using System;

namespace _2020
{
    class d01
    {
        public static void solve(){
            Console.WriteLine("Day 01");
            string file = System.IO.File.ReadAllText(@"../input/01.txt");
            int[] line = new int[file.Split('\n').Length];
            double Part1 = 0; double Part2 = 0;
            // Conversion
            for (int i=0; i<line.Length; i++){
                line[i] = Convert.ToInt32(file.Split('\n')[i]);
            } 
            // Main loop
            for (int y=0; y<line.Length; y++){
                for (int x=0; x<line.Length; x++){
                    if (line[y] + line[x] == 2020){
                        Part1 = line[y]*line[x];
                    }
                    // Part 2
                    for (int z=0; z<line.Length; z++){
                        if (line[y] + line[x] + line[z] == 2020){
                            Part2 = line[y]*line[x]*line[z];
                        }
                    }
                }
            }
            Console.WriteLine($"Part 1: {Part1}");
            Console.WriteLine($"Part 2: {Part2}");
        }
    }
}