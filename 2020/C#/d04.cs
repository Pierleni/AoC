using System;
namespace _2020
{
    class d04
    {
        public static void solve(){
            string data = System.IO.File.ReadAllText(@"../input/04.txt");
            foreach (string passport in data.Split('\n')){
                Console.WriteLine(passport);
            }
        }
    }
}