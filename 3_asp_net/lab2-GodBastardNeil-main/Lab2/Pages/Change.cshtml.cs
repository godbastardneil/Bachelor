using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Lab2.Data;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace Lab2.Pages
{
    public class ChangeModel : PageModel
    {
        private readonly Stud_Info_Repos Repositary;

        [BindProperty(Name = "data")]
        public Stud_Info Stud { get; set; }

        public ChangeModel(Stud_Info_Repos rep)
        {
            Repositary = rep;
            Console.WriteLine($"CreateModel");
        }

        public void OnGet(int id)
        {
            Stud_Info tmp = Repositary.Find(id);
            Console.WriteLine($"OnGet - {tmp.Id}, {tmp.FIO}, {tmp.IsStar}");
            ViewData["dStud"] = tmp;
        }

        public IActionResult OnPost()
        {
            Console.WriteLine($"OnPost - {Stud.Id}, {Stud.FIO}, {Stud.IsStar}");
            Repositary.Update(Stud);
            return RedirectToPage("Index");
        }
    }
}
