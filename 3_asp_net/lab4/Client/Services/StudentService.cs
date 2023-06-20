using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Lab4.Shared.Domain;
using Lab4.Shared.DTO;

namespace Lab4.Client.Services
{
    public class StudentService
    {
        private readonly HttpClient _http;

        public StudentService(HttpClient http)
        {
            _http = http;
        }

        public async Task<IEnumerable<StudentModel>> GetStudent(string idgroup)
        {
            return await _http.GetFromJsonAsync<IEnumerable<StudentModel>>($"api/student/from/{idgroup}");
        }

        public async Task<StudentModel> GetById(string id)
        {
            return await _http.GetFromJsonAsync<StudentModel>($"api/student/idstudent?id={id}");
        }

        public async Task CreateStudent(CreateStudentDTO stud)
        {
            var result = await _http.PostAsJsonAsync($"api/student", stud);

            if (!result.IsSuccessStatusCode)
                throw new ApplicationException("Не получилось добавить студента в группу.");
        }

        public async Task DeleteStudent(StudentModel Student)
        {
            var result = await _http.DeleteAsync($"api/student?id={Student.idstudent}");

            if (!result.IsSuccessStatusCode)
                throw new ApplicationException("Не получилось удалить студента из группы.");
        }

        public async Task UpdateStudent(StudentModel Student)
        {
            var result = await _http.PatchAsync($"api/student",
                new StringContent(JsonSerializer.Serialize(Student),
                Encoding.UTF8,
                "application/json"));


            if (!result.IsSuccessStatusCode)
                throw new ApplicationException("Не получилось обновить студента.");
        }
    }
}
