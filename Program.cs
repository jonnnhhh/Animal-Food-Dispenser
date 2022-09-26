using System;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;
//hi
namespace CSharpCode
{
    public class Program
    {
        static SerialPort myPort;
       
        public static void StringtoArduino(string ArduinoInput)
        {
            string ArduinoOutput;
            myPort = new SerialPort(); // Create a new SerialPort object with default settings.

            // configure the port
            myPort.PortName = "COM6";
            myPort.BaudRate = 9600;
            myPort.ReadTimeout = 10000;
            myPort.WriteTimeout = 10000;

            myPort.Open(); //open port

            myPort.WriteLine(ArduinoInput); //string written to port
            ArduinoOutput = "";
            int i = 0;

            // try to read the port
            // continue trying if message is blank or until 30 timeouts
            while (ArduinoOutput == "" && i != 30)
            {
                try
                {
                    ArduinoOutput = myPort.ReadLine();
                    Console.WriteLine(ArduinoOutput);
                }
                catch (TimeoutException) { }

                i++;
            }

            myPort.Close();
        }
        public static void Main()
                {

            char   mode,resetHolder;

            int    timeInterval_dog_int, dutyCycle_dog_int, timeInterval_cat_int, dutyCycle_cat_int,
                   modeSTATE, reset = 0, 
                   modeFlag = 0;

            string timeInterval_dog, dutyCycle_dog, timeInterval_dog_String, dutyCycle_dog_String,
                   timeInterval_cat, dutyCycle_cat, timeInterval_cat_String, dutyCycle_cat_String,
                   stitch, reset_string, modeFlag_string;

            while (true)
            {
                modeSTATE = 0;
                reset = 0;

                while (modeSTATE != 1)
                {

                    Console.WriteLine("-----------------------------------------------------------------\n");
                    Console.WriteLine("                WELCOME TO THE FOOD DISPENSER                    \n");
                    Console.WriteLine("        Enter feeding mode : (a = Automatic, m = manual)         \n");
                    mode = Console.ReadKey().KeyChar;
                    Console.WriteLine("\n");

                    switch (mode)
                    {
                        case 'a':
                            {
                                Console.WriteLine("-----------------------------------------------------------------\n");
                                Console.WriteLine("You are now in Automatic mode\n");
                                Console.WriteLine("-----------------------------------------------------------------\n");
                                Console.WriteLine("Enter feeding time interval for DOG (0 - 999) minute(s):\n");

                                timeInterval_dog_String = ("");
                                timeInterval_dog = Console.ReadLine();
                                timeInterval_dog_int = Convert.ToInt32(timeInterval_dog);
                                timeInterval_dog_String = String.Format("{0:000}", timeInterval_dog_int);

                                Console.WriteLine("DT value: "+ timeInterval_dog_String + " \n");

                                if (timeInterval_dog_String.Length == 3)
                                {

                                    Console.WriteLine("-----------------------------------------------------------------\n");
                                    Console.WriteLine("Enter amount of DOG food released (0 - 99) %:\n");

                                    dutyCycle_dog_String = ("");
                                    dutyCycle_dog = Console.ReadLine();
                                    dutyCycle_dog_int = Convert.ToInt32(dutyCycle_dog);
                                    dutyCycle_dog_String = String.Format("{0:00}", dutyCycle_dog_int);


                                    if (dutyCycle_dog_String.Length == 2)
                                    {
                                        Console.WriteLine("-----------------------------------------------------------------\n");
                                        Console.WriteLine(dutyCycle_dog + "% of the DOG food will be released every " + timeInterval_dog + " minute(s).\n");
                                        Console.WriteLine("-----------------------------------------------------------------\n");

                                        Console.WriteLine("Enter feeding time interval for CAT (0 - 999) minute(s):\n");

                                        timeInterval_cat_String = ("");
                                        timeInterval_cat = Console.ReadLine();
                                        timeInterval_cat_int = Convert.ToInt32(timeInterval_cat);
                                        timeInterval_cat_String = String.Format("{0:000}", timeInterval_cat_int);

                                        if (timeInterval_cat_String.Length == 3)
                                        {

                                            Console.WriteLine("-----------------------------------------------------------------\n");
                                            Console.WriteLine("Enter amount of CAT food released (1 - 99) %:\n");

                                            dutyCycle_cat_String = ("");
                                            dutyCycle_cat = Console.ReadLine();
                                            dutyCycle_cat_int = Convert.ToInt32(dutyCycle_cat);
                                            dutyCycle_cat_String = String.Format("{0:00}", dutyCycle_cat_int);

                                            if (dutyCycle_cat_String.Length == 2)
                                            {
                                                Console.WriteLine("-----------------------------------------------------------------\n");
                                                Console.WriteLine(dutyCycle_cat + "% of the CAT food will be released every " + timeInterval_cat + " minute(s).\n");
                                                Console.WriteLine("-----------------------------------------------------------------\n");

                                                Console.WriteLine("PRESS r TO RETURN TO MODE MENU.\n");
                                                Console.WriteLine("-----------------------------------------------------------------\n");

                                                modeFlag = 1;
                                                reset = 0;

                                                reset_string = reset.ToString();
                                                modeFlag_string = modeFlag.ToString();
                                                stitch = reset_string + modeFlag_string + timeInterval_dog_String + dutyCycle_dog_String + timeInterval_cat_String + dutyCycle_cat_String;

                                                StringtoArduino(stitch);
                                                

                                                Console.WriteLine("String Data:" + stitch);

                                                resetHolder = Console.ReadKey().KeyChar;

                                                Console.WriteLine("\n" + resetHolder);

                                                if (resetHolder == 'r' || resetHolder == 'R')
                                                {
                                                    resetHolder = '0';
                                                    reset = 1;
                                                    modeFlag = 0;

                                                    timeInterval_dog = "000";
                                                    dutyCycle_dog = "00";
                                                    timeInterval_cat = "000";
                                                    dutyCycle_cat = "00";

                                                    reset_string = reset.ToString();
                                                    modeFlag_string = modeFlag.ToString();
                                                    stitch = reset_string + modeFlag_string + timeInterval_dog + dutyCycle_dog + timeInterval_cat + dutyCycle_cat;

                                                    Console.WriteLine("String Data: " + stitch + "\n");

                                                    modeSTATE = 1;

                                                    Console.WriteLine("\nmodeState = " + modeSTATE + "\n");
                                                }
                                            }
                                            else
                                            {
                                                Console.WriteLine("\nValue Limit has been exceeded, returning to main menu...\n");
                                            }
                                        }
                                        else
                                        {
                                            Console.WriteLine("\nValue Limit has been exceeded, returning to main menu...\n");
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("\nValue Limit has been exceeded, returning to main menu...\n");
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("\nValue Limit has been exceeded, returning to main menu...\n");

                                    modeSTATE = 1;

                                }

                                break;
                            }
                        case 'm':
                            {

                                Console.WriteLine("-----------------------------------------------------------------\n");
                                Console.WriteLine("Manual Mode\n");
                                Console.WriteLine("-----------------------------------------------------------------\n");
                                Console.WriteLine("PRESS r TO RETURN TO MODE MENU.\n");
                                Console.WriteLine("-----------------------------------------------------------------\n");

                                reset = 0;

                                resetHolder = Console.ReadKey().KeyChar;
                                Console.WriteLine("\n");

                                if (resetHolder == 'r')
                                {
                                    resetHolder = '0';
                                    modeSTATE = 1;
                                }

                                break;
                            }
                        default:
                            {
                                Console.WriteLine("\nIncorrect key entered, returning to main menu...\n");
                                modeSTATE = 1;
                                break;
                            }
                    }
                }
            }

        }

    }
}
