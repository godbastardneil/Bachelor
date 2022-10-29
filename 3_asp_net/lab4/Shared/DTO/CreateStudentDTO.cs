using System;
namespace Lab4.Shared.DTO
{
    /// <summary>
    /// Класс данных - студент
    /// </summary>
    public class CreateStudentDTO
    {
        public string FIO { get; set; }
        public bool headman_sign { get; set; }
        public Guid idgroup { get; set; }
    }
}
