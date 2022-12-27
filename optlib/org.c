/*
 * Generated by ./misc/optlib2c from optlib/org.ctags, Don't edit this manually.
 */
#include "general.h"
#include "parse.h"
#include "routines.h"
#include "field.h"
#include "xtag.h"


static void initializeOrgParser (const langType language)
{
	addLanguageOptscriptToHook (language, SCRIPT_HOOK_PRELUDE,
		"{{    /kindTable [\n"
		"        /part\n"
		"        /chapter\n"
		"        /section\n"
		"        /subsection\n"
		"        /subsubsection\n"
		"        /paragraph\n"
		"        /subparagraph\n"
		"    ] def\n"
		"}}");

	addLanguageRegexTable (language, "toplevel");
	addLanguageRegexTable (language, "srcblock");

	addLanguageTagMultiTableRegex (language, "toplevel",
	                               "^[^#*<]+",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "toplevel",
	                               "^#\\+begin_src[ ]+([a-zA-Z0-9][-#+a-zA-Z0-9]*)",
	                               "", "", "{tenter=srcblock}{_guest=\\1,0end,}", NULL);
	addLanguageTagMultiTableRegex (language, "toplevel",
	                               "^(\\*{1,7})[ \t]+([[:graph:][:blank:]]+)([\n])?",
	                               "", "", ""
		"{{\n"
		"    \\2 kindTable \\1 length 1 sub get @2 _tag _commit pop\n"
		"}}", NULL);
	addLanguageTagMultiTableRegex (language, "toplevel",
	                               "^<<([^>]+)>>",
	                               "\\1", "d", "", NULL);
	addLanguageTagMultiTableRegex (language, "toplevel",
	                               "^#\\+(NAME|name):[[:blank:]]+([[:graph:][:blank:]]+)([\n])?",
	                               "\\2", "d", "", NULL);
	addLanguageTagMultiTableRegex (language, "toplevel",
	                               "^.",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "srcblock",
	                               "^[:blank:]*#\\+end_src",
	                               "", "", "{tleave}{_guest=,,0end}", NULL);
	addLanguageTagMultiTableRegex (language, "srcblock",
	                               "^.",
	                               "", "", "", NULL);
}

extern parserDefinition* OrgParser (void)
{
	static const char *const extensions [] = {
		"org",
		NULL
	};

	static const char *const aliases [] = {
		NULL
	};

	static const char *const patterns [] = {
		NULL
	};

	static kindDefinition OrgKindTable [] = {
		{
		  true, 'd', "definition", "definitions",
		},
		{
		  true, 'p', "part", "parts",
		},
		{
		  true, 'c', "chapter", "chapters",
		},
		{
		  true, 's', "section", "sections",
		},
		{
		  true, 'u', "subsection", "subsections",
		},
		{
		  true, 'b', "subsubsection", "subsubsections",
		},
		{
		  true, 'P', "paragraph", "paragraphs",
		},
		{
		  true, 'G', "subparagraph", "subparagraphs",
		},
	};

	parserDefinition* const def = parserNew ("Org");

	def->versionCurrent= 0;
	def->versionAge    = 0;
	def->enabled       = true;
	def->extensions    = extensions;
	def->patterns      = patterns;
	def->aliases       = aliases;
	def->method        = METHOD_NOT_CRAFTED|METHOD_REGEX;
	def->useCork       = CORK_QUEUE;
	def->kindTable     = OrgKindTable;
	def->kindCount     = ARRAY_SIZE(OrgKindTable);
	def->initialize    = initializeOrgParser;

	return def;
}
