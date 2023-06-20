using System;
using System.ComponentModel.DataAnnotations;
namespace Lab4.Shared.Domain
{
    /// <summary>
    /// Simple POCO class for work with Data
    /// </summary>
    public class StudentModel
    {
        [Key]
        public Guid idstudent { get; set; }

        // TODO: Add attributes here
        public string FIO { get; set; }
        public bool headman_sign { get; set; }
        public Guid idgroup { get; set; }
    }
}
