
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;

namespace tmp
{
    class Program
    {
        class PortInfo
        {
            public int PortNumber { get; set; }
            public string Local { get; set; }
            public string Remote { get; set; }
            public string State { get; set; }

            public PortInfo(int i, string local, string remote, string state)
            {
                PortNumber = i;
                Local = local;
                Remote = remote;
                State = state;
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Active TCP Listeners");
            IPGlobalProperties properties = IPGlobalProperties.GetIPGlobalProperties();
            
            IPEndPoint[] endPoints =  properties.GetActiveTcpListeners();
            
            TcpConnectionInformation[] tcpConnections = properties.GetActiveTcpConnections();

            List<PortInfo> pi = (tcpConnections.Select(p =>
                                {
                                    return new PortInfo(
                                        i: p.LocalEndPoint.Port,
                                        local: String.Format("{0}:{1}", p.LocalEndPoint.Address, p.LocalEndPoint.Port),
                                        remote: String.Format("{0}:{1}", p.RemoteEndPoint.Address, p.RemoteEndPoint.Port),
                                        state: p.State.ToString());
                                }).ToList());

            foreach(PortInfo p in pi)
            {
                Console.WriteLine("PortNumber: " + p.PortNumber);
                Console.WriteLine("\tLocal: " + p.Local);
                Console.WriteLine("\tRemote: " + p.Remote);
                Console.WriteLine("\tState: " + p.State);
            }
        }
    }
}
