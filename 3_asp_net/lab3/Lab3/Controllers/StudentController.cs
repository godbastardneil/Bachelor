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
    public class StudentController : Controller
    {
        private StudentRepository SR;
        private GroupRepository GR;

        private readonly ILogger<StudentController> _logger;

        public StudentController(ILogger<StudentController> logger, StudentRepository rep, GroupRepository rep_of_group)
        {
            _logger = logger;
            SR = rep;
            GR = rep_of_group;
        }

        public async Task<IActionResult> Index(int Id)
        {
            ViewBag.idgroup = Id;
            ViewBag.name = (await GR.GetById(Id)).name;
            return View(await SR.List(Id));
        }

        [HttpGet]
        public async Task<IActionResult> Create(int Id)
        {
            ViewBag.idgroup = Id;
            ViewBag.name = (await GR.GetById(Id)).name;
            return View();
        }
        [HttpPost]
        public async Task<IActionResult> Create(StudentModel st)
        {
            await SR.Add(st);
            return RedirectToAction("Index", new { Id = st.idgroup });
        }
        [HttpGet]
        public async Task<IActionResult> Update(int Id)
        {
            var st_to_upd = await SR.GetById(Id);
            ViewBag.name = (await GR.GetById(st_to_upd.idgroup)).name;
            return View(st_to_upd);
        }
        [HttpPost]
        public async Task<IActionResult> Update(StudentModel st)
        {
            await SR.Update(st);
            return RedirectToAction("Index", new { Id = st.idgroup });
        }
        [HttpPost]
        public async Task<IActionResult> Delete(int Id)
        {
            await SR.Remove(Id);
            return Redirect(Request.Headers["Referer"].ToString());
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
