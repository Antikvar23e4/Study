using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC06.Controllers
{
    public class TMResearch : Controller
    {

        // GET:/MResearch/M01/1, /MResearch/M01, /MResearch, /, /V2/MResearch/M01, /V3/MResearch/{string}/M01
        public IActionResult M01()
        {
            return Content("GET:M01");
        }

        // GET: /V2, /V2/MResearch, /V2/MResearch/M02, /MResearch/M02, /V3/MResearch/{string}/M02
        public IActionResult M02()
        {
            return Content("GET:M02");
        }

        // GET: /V3, /V3/MResearch/{string}, /V3/MResearch/{string}/M03
        public IActionResult M03()
        {
            return Content("GET:M03");
        }

        // GET: Любой другой URI
        public IActionResult MXX()
        {
            return Content("GET:MXX");
        }
    }
}
