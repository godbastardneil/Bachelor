using System;
using System.ComponentModel.DataAnnotations;

namespace Lab3.Models
{
    /// <summary>
    /// Simple POCO class for work with Data
    /// </summary>
    public class StudentModel
    {
        [Key]
        public int idstudent { get; set; }

        // TODO: Add attributes here
        public string FIO { get; set; }
        public bool headman_sign { get; set; }
        public int idgroup { get; set; }
        
        public StudentModel() {}
        public StudentModel(int id, string fio, bool hs, int idgr)
        {
            this.idstudent = id;
            this.FIO = fio;
            this.headman_sign = hs;
            this.idgroup = idgr;
        }
        public StudentModel(string fio, bool hs, int idgr)
        {
            this.FIO = fio;
            this.headman_sign = hs;
            this.idgroup = idgr;
        }
    }
}
