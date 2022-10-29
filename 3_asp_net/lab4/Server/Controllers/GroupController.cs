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
    [Route("api/group")]
    public class GroupController : ControllerBase
    {
        private GroupRepository _repository;
        private readonly ILogger<GroupController> _logger;
        public GroupController(ILogger<GroupController> logger, GroupRepository repository)
        {
            _repository = repository;
            _logger = logger;
        }

        [HttpGet("")]
        public async Task<ActionResult<IEnumerable<GroupModel>>> GetAll()
        {
            return Ok(await _repository.List(User.FindFirstValue(ClaimTypes.NameIdentifier)));
        }

        [HttpGet("{id}")]
        public async Task<ActionResult<GroupModel>> GetById(Guid id)
        {
            GroupModel group = await _repository.GetById(id);
            
            if (group == null)
                return NotFound(id);

            if (group.UserId == User.FindFirstValue(ClaimTypes.NameIdentifier))
                return Ok(group);

            return Forbid();
        }

        [HttpPost]
        public async Task<ActionResult> Post(CreateGroupDTO param)
        {
            var Group = new GroupModel
            {
                idgroup = Guid.NewGuid(),
                name = param.name,
                UserId = User.FindFirstValue(ClaimTypes.NameIdentifier)
            };

            await _repository.Add(Group);

            return Created("Group", Group);
        }

        [HttpPatch]
        public async Task<IActionResult> Patch(GroupModel newGroup)
        {
            if (newGroup == null)
                return NotFound();

            GroupModel oldGroup = await _repository.GetById(newGroup.idgroup);

            if (oldGroup == null)
                return NotFound(newGroup.idgroup);

            string userId = User.FindFirstValue(ClaimTypes.NameIdentifier);
            if (oldGroup.UserId != userId || newGroup.UserId != userId )
                return Forbid();

            await _repository.Update(newGroup);
            return Created("Group", newGroup);
        }
        
        [HttpDelete]
        public async Task<IActionResult> Delete(Guid? id)
        {
            if (!id.HasValue)
                return NotFound();

            GroupModel group = await _repository.GetById(id.Value);
            if (group == null)
                return NotFound(id.Value);

            string userId = User.FindFirstValue(ClaimTypes.NameIdentifier);
            if (group.UserId != userId)
                return Forbid();   

            await _repository.Remove(id.Value);

            return NoContent();
        }
    }
}
