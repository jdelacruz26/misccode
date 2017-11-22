using System;
using System.Collections.Generic;
using System.Linq;


namespace test
{
    class Program
    {
        static void Main()
        {
            double Fa0 = 0;
            double Fb0 = 10000;
            double Fc0 = 0;
            double Fd0 = 100;
            double Ff0 = 10000;
            double DEN;
            double r1;
            double r2;
            double r3;
            List<double> w_var = new List<double>();
            List<double> Fa = new List<double>();
            List<double> Fb = new List<double>();
            List<double> Fc = new List<double>();
            List<double> Fd = new List<double>();
            List<double> Ff = new List<double>();

            List<double> Pa = new List<double>();
            List<double> Pb = new List<double>();
            List<double> Pc = new List<double>();
            List<double> Pd = new List<double>();
            List<double> Pf = new List<double>();



            double Ftot;
            double Ftot0 = Fa0 + Fb0 + Fc0 + Fd0 + Ff0;

            //Partial pressures in bar
            double Ptot0 = 1.5;
            double Pa0 = Ptot0 * Fa0 / Ftot0;
            double Pb0 = Ptot0 * Fb0 / Ftot0;
            double Pc0 = Ptot0 * Fc0 / Ftot0;
            double Pd0 = Ptot0 * Fd0 / Ftot0;
            double Pf0 = Ptot0 * Ff0 / Ftot0;

            //Temperatures in K
            double T = 1073;
            double dw = 0.1;
            w_var.Add(0);
            Fa.Add(Fa0);
            Fb.Add(Fb0);
            Fc.Add(Fc0);
            Fd.Add(Fd0);
            Ff.Add(Ff0);

            Pa.Add(Pa0);
            Pb.Add(Pb0);
            Pc.Add(Pc0);
            Pd.Add(Pd0);
            Pf.Add(Pf0);

            double K1 = 1.198e17 * Math.Exp(-26830 / T) / Math.Pow(100, 2);
            double K2 = 1.767e-2 * Math.Exp(4400 / T);
            double K3 = 2.117e15 * Math.Exp(-22430 / T) / Math.Pow(100, 2);
            //
            double KCH4 = 6.65e-4 * Math.Exp(38280 / 8.314 / T);
            double KCO = 8.23e-5 * Math.Exp(70650 / 8.314 / T);
            double KH2 = 6.12e-9 * Math.Exp(82900 / 8.314 / T);
            double KH2O = 1.77e5 * Math.Exp(-88680 / 8.314 / T);

            double kin1 = 4.2248e15 * Math.Exp(-240100 / 8.314 / T);
            double kin2 = 1.955e6 * Math.Exp(-67130 / 8.314 / T);
            double kin3 = 1.0202e15 * Math.Exp(-243900 / 8.314 / T);
            int count;


            for (int i = 0; i < 250; i++)
            {
                w_var.Add(w_var[i] + dw);
                DEN = 1 + KCH4 * Pf[i] + KCO * Pc[i] + KH2 * Pd[i] + KH2O * Pb[i] / Pd[i];
                r1 = kin1 / Math.Pow(Pd[i], 2.5) / Math.Pow(DEN, 2) * (Pf[i] * Pb[i] - Math.Pow(Pd[i], 3) * Pa[i] / K1);
                r2 = kin2 / Pd[i] / Math.Pow(DEN, 2) * (Pa[i] * Pb[i] - Pd[i] * Pc[i] / K2);
                r3 = kin3 / Math.Pow(Pd[i], 3.5) / Math.Pow(DEN, 2) * (Pf[i] * Math.Pow(Pb[i], 2) - Math.Pow(Pd[i], 4) * Pc[i] / K3);

                Fa.Add(Fa[i] + (r1 - r2) * dw);
                if (Fa[i + 1] < 0)
                {
                    Fa.Insert(i+1,1e-3);
                }

                Fb.Add(Fb[i] - (r1 + r2 + 2 * r3) * dw);
                if (Fb[i + 1] < 0)
                {
                    Fb.Insert(i + 1, 1e-3);
                }

                Fc.Add(Fc[i] + (r2 + r3) * dw);
                if (Fc[i + 1] < 0)
                {
                    Fc.Insert(i + 1, 1e-3);
                }

                Fd.Add(Fd[i] + (3 * r1 + r2 + 4 * r3) * dw);
                if (Fd[i + 1] < 0)
                {
                    Fd.Insert(i + 1, 1e-3);
                }

                Ff.Add(Ff[i] - (r1 + r3) * dw);
                if (Ff[i + 1] < 0)
                {
                    Ff.Insert(i + 1, 1e-3);
                }

                Ftot = Fa[i + 1] + Fb[i + 1] + Fc[i + 1] + Fd[i + 1] + Ff[i + 1];

                Pa.Add(Ptot0 * Fa[i + 1] / Ftot);
                if (Pa[i + 1] < 0)
                {
                    Pa.Insert(i + 1, 1e-3);
                }

                Pb.Add(Ptot0 * Fb[i + 1] / Ftot);
                if (Pb[i + 1] < 0)
                {
                    Pb.Insert(i + 1, 1e-3);
                }

                Pc.Add(Ptot0 * Fc[i + 1] / Ftot);
                if (Pc[i + 1] < 0)
                {
                    Pc.Insert(i + 1, 1e-3);
                }

                Pd.Add(Ptot0 * Fd[i + 1] / Ftot);
                if (Pd[i + 1] < 0)
                {
                    Pd.Insert(i + 1, 1e-3);
                }

                Pf.Add(Ptot0 * Ff[i + 1] / Ftot);
                if (Pf[i + 1] < 0)
                {
                    Pf.Insert(i + 1, 1e-3);
                }
            }
            count = 0;
            Console.Write("Fa Values:");
            Console.Write("             ");
            Console.Write("Fb Values:");
            Console.Write("             ");
            Console.Write("Fc Values:");
            Console.Write("             ");
            Console.Write("Fd Values:");
            Console.Write("             ");
            Console.Write("Ff Values:");
            Console.Write("             ");
            Console.Write("Pa Values:");
            Console.Write("              ");
            Console.Write("Pb Values:");
            Console.Write("              ");
            Console.Write("Pc Values:");
            Console.Write("              ");
            Console.Write("Pd Values:");
            Console.Write("              ");
            Console.WriteLine("Pf Values:");

            foreach (double data in Fa){
                Console.Write(data);
                Console.Write("       ");
                Console.Write(Fb[count]);
                Console.Write("       ");
                Console.Write(Fc[count]);
                Console.Write("       ");
                Console.Write(Fd[count]);
                Console.Write("       ");
                Console.Write(Ff[count]); 
                Console.Write("       ");
                Console.Write(Pa[count]);
                Console.Write("       ");
                Console.Write(Pb[count]);
                Console.Write("       ");
                Console.Write(Pc[count]);
                Console.Write("       ");
                Console.Write(Pd[count]);
                Console.Write("       ");
                Console.WriteLine(Pf[count]);
                count = count + 1;
            }
            Console.Read();
        }
    }
}
    
