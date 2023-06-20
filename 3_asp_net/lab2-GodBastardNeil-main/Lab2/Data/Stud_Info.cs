using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lab2.Data
{
    /// <summary>
    /// Simple POCO class for work with Data
    /// </summary>
    public class Stud_Info
    {

        public int Id { get; set; }

        // TODO: Add attributes here
        public string FIO { get; set; }
        public bool IsStar { get; set; }
    }
}
