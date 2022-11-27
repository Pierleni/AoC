using System;
using System.Collections.Generic;
using System.Linq;

namespace _2020
{
    class Emu
    {
        // Inizializer
        public int accumulator { get;  set; }
        public int ip { get; set; }
        public bool halt { get; set; }
        public List<int> index = new List<int>();
        public List<string> instructions = new List<string>();
        
        // Default var
        public string operation = "";
        public string op = "";
        public int n = 0;
        public string data = System.IO.File.ReadAllText(@"../input/08.txt");
        
        // Constructor
        public Emu(){
            // instruction builder
            foreach (string line in data.Split('\n')){
                instructions.Add(line);
            }
            accumulator = 0;
            halt = false;
            ip = 0;
        }
        // Check for duplicate index
        public bool checkIndex(int n){
            if (index.Contains(n)){
                return true;
            }
            return false;
        }

        // Main Function
        public void run(List<string> instr, bool debug=false){
            ip = 0;
            accumulator = 0;
            while (halt != true && ip < instr.Count()){
                
                // check index
                if (checkIndex(ip) == true) {halt = true; break;} 
                else {index.Add(ip);}

                // Read Instruction
                operation = instr[ip];
                op = operation.Split()[0];
                n = Convert.ToInt32(operation.Split()[1]);
                
                switch (op){
                    case "acc":
                        accumulator += n;
                        ip++;
                        break;

                    case "jmp":
                        ip += n;
                        break;

                    default:
                        ip++;
                        break;
                }
            }
            if (halt == true && debug == false){
                Console.WriteLine($"Test Failed: Accomulator = {accumulator}");
            }
            else if (halt == true && debug == true){
                halt = false;
                index.Clear();
            }
            else {
                Console.WriteLine($"Test Passed: Accomulator = {accumulator}");
            }
        }

        public void debug(){
            for (int i=0; i<instructions.Count(); i++){
                List<string> newInstr = new List<string>();
                
                // Rebuild Instructions
                foreach (string line in data.Split('\n')){
                    newInstr.Add(line);
                }
                // Swap single instruction
                string numero = instructions[i].Split()[1];
                
                if (instructions[i].Split()[0] == "nop"){
                    newInstr[i] = "jmp " + numero;
                } else if (instructions[i].Split()[0] == "jmp"){
                    newInstr[i] = "nop " + numero;
                }
                // Run it
                run(newInstr, true);
            }
        }
    }
    
    
    
    class d08
    {
        public static void solve(){
            Console.WriteLine("Day 08");

            Emu emu = new Emu();
            // Part 1
            emu.run(emu.instructions);
            // Part 2
            emu.debug();
        }
    }
}