using Lab2.Data;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lab2.Pages
{
    public class IndexModel : PageModel
    {
        private readonly Stud_Info_Repos Repositary;

        public IndexModel(Stud_Info_Repos rep)
        {
            Repositary = rep;
        }

        public void OnGet()
        {
            ViewData["data"] = Repositary.Read_List();
        }

        public IActionResult OnPostDelete(int id)
        {
            Console.WriteLine($"del - {id}");
            Repositary.Remove(id);
            return RedirectToPage("Index");
        }
    }
}
