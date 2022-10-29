using System;
using System.ComponentModel.DataAnnotations;
namespace Lab4.Shared.Domain
{
    /// <summary>
    /// Simple POCO class for work with Data
    /// </summary>
    public class GroupModel
    {
        [Key]
        public Guid idgroup { get; set; }

        // TODO: Add attributes here
        public string name { get; set; }
        public string UserId { get; set; }


    }
}
