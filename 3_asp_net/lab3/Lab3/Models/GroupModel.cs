using System;
using System.ComponentModel.DataAnnotations;

namespace Lab3.Models
{
    /// <summary>
    /// Simple POCO class for work with Data
    /// </summary>
    public class GroupModel
    {
        [Key]
        public int idgroup { get; set; }

        // TODO: Add attributes here
        public string name { get; set; }
        public GroupModel() {}
        public GroupModel(int Id, string Name)
        {
            this.idgroup = Id;
            this.name = Name;
        }
        public GroupModel(string Name)
        {
            this.name = Name;
        }

    }
}
