using Lab4.Shared.DTO;
using Lab4.Shared.Domain;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Lab4.Server.Repositories;
using System.Security.Claims;

namespace Lab4.Server.Controllers
{
    [Authorize]
    [ApiController]
    [Route("api/student")]
    public class StudentController : ControllerBase
    {
        private GroupRepository GRRepository;
        private StudentRepository SRRepository;
        private readonly ILogger<StudentController> _logger;
        public StudentController(ILogger<StudentController> logger, StudentRepository StudRepository, GroupRepository GrRepository)
        {
            GRRepository = GrRepository;
            SRRepository = StudRepository;
            _logger = logger;
        }

        [HttpGet("from/{id}")]
        public async Task<ActionResult<IEnumerable<StudentModel>>> GetAll(Guid id)
        {
            GroupModel group = await GRRepository.GetById(id);

            if (group == null)
                return NotFound(id);

            if (group.UserId == User.FindFirstValue(ClaimTypes.NameIdentifier))
                return Ok(await SRRepository.List(id));

            return Forbid();
        }

        [HttpGet]
        [Route("idstudent")]
        public async Task<ActionResult<StudentModel>> GetById(Guid id)
        {
            StudentModel student = await SRRepository.GetById(id);

            if (student == null)
                return NotFound(id);

            GroupModel group = await GRRepository.GetById(student.idgroup);

            if (group.UserId == User.FindFirstValue(ClaimTypes.NameIdentifier))
                return Ok(student);

            return Forbid();
        }

        [HttpPost]
        public async Task<ActionResult> Post(CreateStudentDTO param)
        {
            GroupModel group = await GRRepository.GetById(param.idgroup);

            if (group == null)
                return NotFound();

            if (group.UserId != User.FindFirstValue(ClaimTypes.NameIdentifier))
                return Forbid();

            var stud = new StudentModel
            {
                idstudent = Guid.NewGuid(),
                FIO = param.FIO,
                headman_sign = param.headman_sign,
                idgroup = param.idgroup
            };

            await SRRepository.Add(stud);

            return Created("Student", stud);
        }

        [HttpPatch]
        public async Task<IActionResult> Patch(StudentModel newStudent)
        {
            if (newStudent == null)
                return NotFound();

            StudentModel oldStudent = await SRRepository.GetById(newStudent.idstudent);

            if (oldStudent == null)
                return NotFound(newStudent.idgroup);

            GroupModel oldGroup = await GRRepository.GetById(oldStudent.idgroup);
            GroupModel newGroup = await GRRepository.GetById(newStudent.idgroup);

            string userId = User.FindFirstValue(ClaimTypes.NameIdentifier);
            if (oldGroup.UserId != userId || newGroup.UserId != userId)
                return Forbid();

            await SRRepository.Update(newStudent);

            return Created("Student", newStudent);
        }

        [HttpDelete]
        public async Task<IActionResult> Delete(Guid id)
        {

            StudentModel student = await SRRepository.GetById(id);

            if (student == null)
                return NotFound(id);

            GroupModel group = await GRRepository.GetById(student.idgroup);

            string userId = User.FindFirstValue(ClaimTypes.NameIdentifier);
            if (group.UserId != userId)
                return Forbid();

            await SRRepository.Remove(id);

            return NoContent();
        }
    }
}
