using Lab3.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

namespace Lab3.Controllers
{
    public class GroupController : Controller
    {
        private GroupRepository GR;

        private readonly ILogger<GroupController> _logger;

        public GroupController(ILogger<GroupController> logger, GroupRepository rep)
        {
            _logger = logger;
            GR = rep;
        }

        public async Task<IActionResult> Index()
        {
            return View(await GR.List());
        }

        [HttpGet]
        public IActionResult Create()
        {
            return View();
        }
        [HttpPost]
        public async Task<IActionResult> Create(GroupModel gr)
        {
            await GR.Add(gr);
            return RedirectToAction("Index");
        }
        [HttpGet]
        public async Task<IActionResult> Update(int Id)
        {
            return View(await GR.GetById(Id));
        }
        [HttpPost]
        public async Task<IActionResult> Update(GroupModel gr)
        {
            await GR.Update(gr);
            return RedirectToAction("Index");
        }
        [HttpPost]
        public async Task<IActionResult> Delete(int Id)
        {
            await GR.Remove(Id);
            return RedirectToAction("Index");
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
