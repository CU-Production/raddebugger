// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

////////////////////////////////
//~ rjf: Build Settings

#define RADDBG_VERSION_MAJOR 0
#define RADDBG_VERSION_MINOR 9
#define RADDBG_VERSION_PATCH 0
#define RADDBG_VERSION_STRING_LITERAL Stringify(RADDBG_VERSION_MAJOR) "." Stringify(RADDBG_VERSION_MINOR) "." Stringify(RADDBG_VERSION_PATCH)
#if defined(NDEBUG)
# define RADDBG_TITLE_STRING_LITERAL "The RAD Debugger (" RADDBG_VERSION_STRING_LITERAL " ALPHA) - " __DATE__ ""
#else
# define RADDBG_TITLE_STRING_LITERAL "The RAD Debugger (" RADDBG_VERSION_STRING_LITERAL " ALPHA) - " __DATE__ " [Debug]"
#endif

#define ENABLE_DEV 1
#define DE2CTRL 1

////////////////////////////////
//~ rjf: Hot, High Priority Tasks (Complete Unusability, Crashes, Fire-Worthy)
//
// [ ] ** Thread/process control bullet-proofing, including solo-step mode
// [ ] ** Converter performance & heuristics for asynchronously doing it early
// [ ] ** high refresh rate, but consistently missing tight frame deadline,
//     animation
// [ ] ** ASAN targets
//
// [ ] ** I can't seem to get the .raddbg files to update consistently, or
//     something. I can't seem to reproduce it reliably, but sometimes when I
//     rebuild, for example, it seems to keep using the old PDB data
//     effectively - like it doesn't think it needs to update the raddbg file,
//     or something? But if I manually delete the raddbg file and relaunch,
//     then it will have the new debug info. It would be nice if there was
//     some kind of way to interrogate this in the debugger so I can send a
//     more constructive report, like some way to get a hash of the PDB that
//     is thinks it has converted to the RAD format, and then a way I can hash
//     the PDB on the drive, or something, so I can figure out if they are
//     mismatching for sure?
//
// [ ] ** In solo-stepping mode, if I step over something like CreateFileA, it
//     pseudo-hangs the debugger. I can't seem to do anything else, including
//     "Kill All". I have to close the debugger and restart it, AFAICT?
//
// [ ] ** I tried to debug a console program, and "step into" didn't seem to
//     work. Instead, it just started running the program, but the program
//     seemed to hang, and then the debugger pseudo-hung with a continual
//     progress bar in the disassembly window. I had to close and restart. Is
//     console app debugging not working yet, perhaps?
//
// [ ] ** If you put a full path to a TTF font into the code_font/main_font
//     variables of the config file, it continually rewrites it each time you
//     launch. The first time you launch, with your hand-edited font path, it
//     works correctly and the font loads, but it rewrites it from an absolute
//     path to a relative path. The second time you launch, with the relative
//     path, it doesn't work (you get no text at all), and it rewrites it from
//     relative back to absolute, but to the wrong path (prepending
//     C:/users/casey/AppData/ to the previous path, even though that was not
//     at all where the font ever was) The font path will now remain "stable"
//     in the sense that it won't rewrite it anymore. But you cannot use the
//     debugger because it's the wrong font path, so you get no text.
//  [ ] Setting the code_font/main_font values to a font name doesn't work.
//      Should probably make note that you have to set it to a path to a TTF,
//      since that's not normally how Windows fonts work.
//
// [ ] Launching the debugger with an invalid code_font/main_font name doesn't
//     have any fallback, so you just get no text at all. Probably should use
//     a fallback font when font loading fails
//
// [ ] disasm animation & go-to-address
//
// [ ] visualize mismatched source code and debug info
// [ ] visualize remapped files (via path map)

////////////////////////////////
//~ rjf: Hot, Medium Priority Tasks (Low-Hanging-Fruit Features, UI Jank, Cleanup)
//
//  [ ] I was a little confused about what a profile file was. I understood
//      what the user file was, but the profile file sounded like it should
//      perhaps be per-project, yet it sounded like it was meant to be somewhat
//      global? I don't have any feedback here because it probably will make
//      sense once I use the debugger more, but I just thought I'd make a note
//      to say that I was confused about it after reading the manual, so
//      perhaps you could elaborate a little more on it in there.
//
// [ ] ** "Find Name" may not be working as advertised. In the description, it
//     says you can jump to a file, but if I type in the complete filename of
//     a file in the project and hit return, it just turns red and says it
//     couldn't find it. This happens even if the file is already open in a
//     tab.
//   [ ] "Find Name" would be a lot more useful if you could type partial
//       things, and it displayed a list, more like what happens in a
//       traditional text editor. Typing the entire name of a function to jump
//       to it is too laborious.
//
// [ ] Right-clicking on a thread in the Scheduler window pops up a context
//     menu, but you can't actually see it because the tooltip for the thread
//     draws on top of it, so you can't see the menu.
//
//  [ ] In a "hover watch" (where you hover over a variable and it shows a pop-
//      up watch window), if you expand an item near the bottom of the listing,
//      it will be clipped to the bottom of the listing instead of showing the
//      actual items (ie., it doesn't resize the listing based on what's
//      actually visible)
//
//  [ ] ** Function breakpoints should show up in the source listing. Without
//      them being visible, it is confusing when you run and you stop there,
//      because you're like "wait why did it stop" and then you later remember
//      that's because there was a function breakpoint there.
//
//  [ ] ** One very nice feature of RemedyBG that I use all the time is the
//      ability to put "$err, hr" into the watch window, which will just show
//      the value of GetLastError() as a string. This is super useful for
//      debugging, so you don't have to litter your own code with it.
//
//  [ ] Tooltip Coverage:
//   [ ] lock icon
//   [ ] "rotation arrow" icon next to executables
//
//  [ ] Using the word "symbol" in "Code (Symbol)" seems like a bad idea, since
//      you're referring to non-identifier characters, but in a debugger
//      "symbol" usually means something defined in the debug information.
//
//  [ ] I LOVE ALT-W to add watch under cursor, but I would prefer to have it
//      add what's under the MOUSE cursor instead of the keyboard cursor. Can
//      we get a command for that so I can bind ALT-W to that instead?
//
//  [ ] For theme editing, when you hove the mouse over a theme color entry and
//      it highlights that entry, it might help to temporarily change that
//      color to white (or the inverse of the background color, or whatever) so
//      that the user can see what things on the screen use that theme color.
//
//  [ ] I couldn't figure out how to affect the "dim" color in constants that
//      have alternating bright/dim letters to show sections of a number. Is
//      this in the theme colors somewhere?
//
//  [ ] For breakpoint-on-function, it would be great if it showed a list of
//      (partial) matches as you type, so you can stop typing once it gets the
//      right function instead of having to type the entire function name.
//
//  [ ] Hovering over a source tab that is clipped should probably display the
//      full thing that was in that tab (like the whole filename, etc.). Right
//      now, hovering does nothing AFAICT.
//
//  [ ] ** I couldn't figure out how to really view threads in the debugger.
//      The only place I found a thread list was in "The Scheduler", but it
//      only lists threads by ID, which is hard to use. I can hover over them
//      to get the stack, which helps, but it would be much nicer if the top
//      function was displayed in the window by default next to the thread.
//  [ ] ** It would be nice if thread listings displayed the name of the
//      thread, instead of just the ID.
//
//  [ ] ** Scrollbars are barely visible for me, for some reason. I could not
//      find anything in the theme that would fill them with a solid, bright
//      color. Instead they are just a thin outline and the same color as the
//      scroll bar background.
//
//  [ ] Dragging a window tab (like Locals or Registers or whatnot) and
//      canceling with ESC should revert the window tab to where it was.
//      Currently, it leaves the window tab reordered if you dragged over its
//      window and shuffled its position.
//
//  [ ] Many of the UI elements, like the menus, would like better if they had
//      a little bit of margin. Having the text right next to the edges, and
//      with no line spacing, makes it harder to read things quickly.
//
//  [ ] Menus take too long to show up. I would prefer it if they were instant.
//      The animation doesn't really provide any useful cues, since I know
//      where the menu came from.
//
//  [ ] Theme window should include font scaling. I was able to find the
//      command for increasing the font scale, but I imagine most people
//      wouldn't think to look there.
//  [ ] I had to go into the user file to change the font. That should probably
//      be in the theme window?
//
//  [ ] The way the "commands" view worked was idiosyncratic. All the other
//      views stay up, but that one goes away whenever I select a command for
//      some reason.
//   [ ] Also, I could not move the commands window anywhere AFAICT. It seems
//       to just pop up over whatever window I currently have selected. This
//       would make sense for a hotkey (which I assume is the way it was
//       designed), but it seems like it should be permanent if you can select
//       it from the View menu.
//  [ ] If the command window is not wide enough, you cannot read the
//      description of a command because it doesn't word-wrap, nor can you
//      hover over it to get the description in a tooltip (AFAICT).
//
//  [ ] It'd be nice to have a "goto byte" option for source views, for jumping
//      to error messages that are byte-based instead of line-based.
//
//  [ ] Pressing the left mouse button on the menu bar and dragging does not
//      move through the menus as expected - instead, it opens the one you
//      clicked down on, then does nothing until you release, at which point it
//      opens the menu you released on.
//  [ ] Similarly, pressing the left mouse button on a menu and dragging to an
//      item, then releasing, does not trigger that item as expected. Instead,
//      it is a nop, and it waits for you to click again on the item.
//
//  [ ] Working with panels felt cumbersome. I couldn't figure out any way to
//      quickly arrange the display without manually selecting "split panel"
//      and "close panel" and stuff from the menu, which took a long time.
//   - @polish @feature ui for dragging tab -> bundling panel split options
//
//  [ ] I found the "context menu" convention to be confusing. For example, if
//      I left-click on a tab, it selects the tab. If I right-click on a tab,
//      it opens the context menu. However, if I left-click on a module, it
//      opens the context window. It seems like maybe menus should be right,
//      and left should do the default action, more consistently?
//
//  [ ] Hovering over disassembly highlights blocks of instructions, which I
//      assume correspond to source lines. But perhaps it should also highlight
//      the source lines? The inverse hover works (you hover over source, and
//      it highlights ASM), but ASM->source doesn't.
//
//  [ ] It wasn't clear to me how you save a user or profile file. I can see
//      how to load them, but not how you save them. Obviously I can just copy
//      the files myself in the shell, but it seemed weird that there was no
//      "save" option in the menus.
//
// [ ] @cleanup @feature double & triple click select in source views
// [ ] @feature hovering truncated text in UI for some amount of time -> show
//     tooltip with full text
// [ ] @feature disasm keyboard navigation & copy/paste
// [ ] @feature debug info overrides (both path-based AND module-based)
// [ ] configure tab size
// [ ] run-to-line needs to work if no processes are running
//     - place temp bp, attach "die on hit" flag or something like that?
// [ ] auto-scroll output window

////////////////////////////////
//~ rjf: Hot, Low Priority Tasks (UI Opinions, Less-Serious Jank, Preferences, Cleanup)
//
//  [ ] ** In the call stack, I would like to be able to click quickly and move
//      around the stack. Right now, you can do that with the first and third
//      column, but the second column drops down a context menu. Since right
//      click is already for context menus, can it not just be that double-
//      clicking any column jumps to that stack frame?
//
//  [ ] ** I find it really hard to read the code with the heavyweight lines
//      running through it for breakpoints and stepping and things. Is there a
//      way to turn the lines off? AFAICT they are based on thread and
//      breakpoint color, so you can't really control the line drawing? I might
//      be fine with them, but they would have to be much more light (like
//      alpha 0.1 or something)
//
//  [ ] It's confusing that ENTER is the way you expand and collapse things in
//      the watch window, but then also how you edit them if they are not
//      expandable? It seems like this should be consistent (one way to edit,
//      one way to expand/collapse, that are distinct)
//
//  [ ] I didn't understand the terminology "Equip With Color". Does that just
//      mean specify the color used to display it? Is "Apply Color" perhaps a
//      bit more user-friendly?
//
//  [ ] The cursor feels a bit too huge vertically.
//
//  [ ] The hex format for color values in the config file was a real
//      mindbender. It's prefixed with "0x", so I was assuming it was either
//      Windows Big Endian (0xAARRGGBB) or Mac Little Endian (0xAABBGGRR). To
//      my surprise, it was neither - it was actually web format (RRGGBBAA),
//      which I was not expecting because that is normally written with a
//      number sign (#AARRGGBB) not an 0x.
//
//  [ ] Clicking on either side of a scroll bar is idiosyncratic. Normally,
//      that is "page up" / "page down", but here it is "smooth scroll upward"
//      / "smooth scroll downward" for some reason?
//
//  [ ] Hitting ESC during a color picker drag should abort the color picking
//      and revert to the previous color. Currently, it just accepts the last
//      drag result as the new color.
//
//  [ ] It was not clear to me why a small "tab picker" appeared when I got to
//      a certain number of tabs. It seemed to appear even if the tabs were
//      quite large, and there was no need to a drop-down menu to pick them. It
//      feels like either it should always be there, or it should only show up
//      if at least one tab gets small enough to have its name cut off?
//
//  [ ]  can it ignore stepping into _RTC_CheckStackVars generated functions?
//  [ ]  mouse back button should make view to go back after I double clicked
//       on function to open it
//  [ ]  middle mouse button on tab should close it
//  [ ]  pressing random keyboard keys in source code advances text cursor like
//       you were inputting text, very strange.
//  [ ]  Alt+8 to switch to disassembly would be nice (regardless on which
//       panel was previous, don't want to use ctrl+, multiple times)
//       Alt+8 for disasm and Alt+6 for memory view are shortcuts I often use
//       in VS
//  [ ]  what's up with decimal number coloring where every group of 3 are in
//       different color? can I turn it off? And why sometimes digits in number
//       start with brighter color, but sometimes with darker - shouldn't it
//       always have the same color ordering?
//  [ ]  it would be nice to have "show in explorer" for right click on source
//       file tab (opens explorer & selects the file)
//  [ ]  it would be nice if Alt+o in source file would switch between .h and
//       .c/cpp file (just look for same name in same folder)
//  [ ]  in watch window when I enter some new expression and then click mouse
//       away from cell, then it should behave the same as if I pressed enter.
//       Currently it does the same as if I have pressed esc and I have lost my
//       expression
//  [ ]  default font size is too small for me - not only source code, but
//       menus/tab/watch names (which don't resize). Maybe you could query
//       Windows for initial font size?
//  [ ]  zooming behaves very strangely - sometimes it zooms source code,
//       sometimes both source code and menu/tab/watch font size, sometimes
//       just menu/tab/watch font size not source size.
//  [ ]  icon fonts glyphs sometimes disappear for specific font size, but they
//       reappear if you go +1 higher or -1 lower. Mostly red triangle in watch
//       values for "unknown identifier". But also yellow arrow in call stack
//       disappears if font size gets too large.
//  [ ]  undo close tab would be nice. If not for everything, then at least
//       just for source files

////////////////////////////////
//~ rjf: Hot, Feature Tasks (Not really "low priority" but less urgent than fixes)
//
// [ ] For the Scheduler window, it would be nice if you could dim or
//     folderize threads that are not your threads - eg., if a thread doesn't
//     have any resolved stack pointers in your executable code, then you can
//     ignore it when you are focusing on your own code. I don't know what the
//     best way to detect this is, other than by walking the call stack... one
//     way might be to just have a way to separate threads you've named from
//     threads you haven't? Or, there could even be a debugger-specific API
//     that you use to tag them. Just some way that would make it easier to
//     focus on your own threads.
//
// [ ] autocomplete lister should respect position in edited expression,
//     tabbing through should autocomplete but not exit, etc.
//
// [ ] Fancy View Rules
//  [ ] table column boundaries should be checked against *AFTER* table
//      contents, not before
//  [ ] `text[:lang]` - interpret memory as text, in lang `lang`
//  [ ] `disasm:arch` - interpret memory as machine code for isa `arch`
//  [ ] `memory` - view memory in usual memory hex-editor view
//  NOTE(rjf): When the visualization system is solid, layers like dasm, txti,
//  and so on can be dispensed with, as things like the source view, disasm
//  view, or memory view will simply be specializations of the general purpose
//  viz system.
//  [ ] view rule hook for standalone visualization ui, granted its own
//      tab
//
// [ ] search-in-all-files
//
// [ ] Memory View
//  [ ] memory view mutation controls
//  [ ] memory view user-made annotations
//
// [ ] undo/redo
// [ ] proper "go back" + "go forward" history navigations
//
// [ ] globally disable/configure default view rule-like things (string
//     viz for u8s in particular)
// [ ] globally disable/configure bp/ip lines in source view
//
// [ ] @feature processor/data breakpoints
// [ ] @feature automatically snap to search matches when searching source files
// [ ] @feature entity views: filtering & reordering

////////////////////////////////
//~ rjf: Cold, Clean-up Tasks That Probably Only Ryan Notices
// (E.G. Because They Are Code-Related Or Because Nobody Cares)
//
// [ ] @bug view-snapping in scroll-lists, accounting for mapping between
//     visual positions & logical positions (variably sized rows in watch,
//     table headers, etc.)
// [ ] @bug selected frame should be keyed by run_idx or something so that it
//     can gracefully reset to the top frame when running
// [ ] @cleanup collapse DF_CfgNodes into just being MD trees, find another way
//     to encode config source - don't need it at every node
// [ ] @cleanup straighten out index/number space & types & terminology for
//     scroll lists
// [ ] @cleanup simplification pass over eval visualization pipeline & types,
//     including view rule hooks
// [ ] @cleanup naming pass over eval visualization part of the frontend,
//     "blocks" vs. "canvas" vs. "expansion" - etc.
// [ ] @cleanup central worker thread pool - eliminate per-layer thread pools

////////////////////////////////
//~ rjf: Cold, Unsorted Notes (Deferred Until Existing Lists Mostly Exhausted)
//
// [ ] @feature types -> auto view rules (don't statefully fill view rules
//     given types, just query if no other view rule is present, & autofill
//     when editing)
// [ ] @feature eval system -> somehow evaluate breakpoint hit counts? "meta"
//     variables?
// [ ] @feature watch window labels
// [ ] @feature scheduler -> thread grid view?
//
// [ ] @feature disasm view improvement features
//  [ ] interleaved src/dasm view
//  [ ] visualize jump destinations in disasm
//
// [ ] @feature eval ui improvement features
//  [ ] serializing eval view maps
//  [ ] view rule editors in hover-eval
//  [ ] view rule hook coverage
//   [ ] `each:(expr addition)` - apply some additional expression to all
//        elements in an array/linked list would be useful to look at only a
//        subset of an array of complex structs
//   [ ] `slider:(min max)` view rule
//   [ ] `v2f32` view rule
//   [ ] `v3` view rule
//   [ ] `quat` view rule
//   [ ] `matrix` view rule
//   [ ] `audio` waveform view rule
//  [ ] smart scopes - expression operators for "grab me the first type X"
//  [ ] "pinning" watch expressions, to attach it to a particular ctrl_ctx
//
// [ ] @feature header file for target -> debugger communication; printf, log,
//     etc.
// [ ] @feature just-in-time debugging
// [ ] @feature step-out-of-loop
//
//-[ ] long-term future notes from martins
//  [ ] core dump saving/loading
//  [ ] parallel call stacks view
//  [ ] parallel watch view
//  [ ] mixed native/interpreted/jit debugging
//      - it seems python has a top-level linked list of interpreter states,
//        which should allow the debugger to map native callstacks to python
//        code
//
// [ ] fancy string runs can include "weakness" information for text truncation
//     ... can prioritize certain parts of strings to be truncated before
//     others. would be good for e.g. the middle of a path
// [ ] ui code maintenance, simplification, design, & robustness pass
//  [ ] page-up & page-down correct handling in keyboard nav
//  [ ] collapse context menus & command lister into same codepaths. filter by
//      context. parameterize by context.
//  [ ] collapse text cells & command lister & etc. into same codepath (?)
//  [ ] nested context menus
//  [ ] unified top-level cursor/typing/lister helper
//  [ ] font selection lister
// [ ] font cache eviction (both for font tags, closing fp handles, and
//     rasterizations)
// [ ] frontend speedup opportunities
//  [ ] tables in UI -> currently building per-row, could probably cut down on
//      # of boxes and # of draws by doing per-column in some cases?
//  [ ] font cache layer -> can probably cache (string*font*size) -> (run) too
//      (not just rasterization)... would save a *lot*, there is a ton of work
//      just in looking up & stitching stuff repeatedly
//  [ ] convert UI layout pass to not be naive recursive version
//  [ ] (big change) parallelize window ui build codepaths per-panel

////////////////////////////////
//~ rjf: Includes

//- rjf: [h]
#include "base/base_inc.h"
#include "os/os_inc.h"
#include "mdesk/mdesk.h"
#include "hash_store/hash_store.h"
#include "text_cache/text_cache.h"
#include "path/path.h"
#include "txti/txti.h"
#include "coff/coff.h"
#include "pe/pe.h"
#include "raddbg_format/raddbg_format.h"
#include "raddbg_format/raddbg_format_parse.h"
#include "raddbg_cons/raddbg_cons.h"
#include "raddbg_convert/pdb/raddbg_coff.h"
#include "raddbg_convert/pdb/raddbg_codeview.h"
#include "raddbg_convert/pdb/raddbg_msf.h"
#include "raddbg_convert/pdb/raddbg_pdb.h"
#include "raddbg_convert/pdb/raddbg_coff_conversion.h"
#include "raddbg_convert/pdb/raddbg_codeview_conversion.h"
#include "raddbg_convert/pdb/raddbg_from_pdb.h"
#include "raddbg_convert/pdb/raddbg_codeview_stringize.h"
#include "raddbg_convert/pdb/raddbg_pdb_stringize.h"
#include "regs/regs.h"
#include "regs/raddbg/regs_raddbg.h"
#include "type_graph/type_graph.h"
#include "dbgi/dbgi.h"
#include "demon/demon_inc.h"
#include "eval/eval_compiler.h"
#include "eval/eval_machine.h"
#include "eval/eval_parser.h"
#include "unwind/unwind.h"
#include "ctrl/ctrl_inc.h"
#include "dasm/dasm.h"
#include "font_provider/font_provider_inc.h"
#include "render/render_inc.h"
#include "texture_cache/texture_cache.h"
#include "geo_cache/geo_cache.h"
#include "font_cache/font_cache.h"
#include "draw/draw.h"
#include "ui/ui_inc.h"
#include "df/df_inc.h"

//- rjf: [c]
#include "base/base_inc.c"
#include "os/os_inc.c"
#include "mdesk/mdesk.c"
#include "hash_store/hash_store.c"
#include "text_cache/text_cache.c"
#include "path/path.c"
#include "txti/txti.c"
#include "coff/coff.c"
#include "pe/pe.c"
#include "raddbg_format/raddbg_format.c"
#include "raddbg_format/raddbg_format_parse.c"
#include "raddbg_cons/raddbg_cons.c"
#include "raddbg_convert/pdb/raddbg_msf.c"
#include "raddbg_convert/pdb/raddbg_codeview.c"
#include "raddbg_convert/pdb/raddbg_pdb.c"
#include "raddbg_convert/pdb/raddbg_coff_conversion.c"
#include "raddbg_convert/pdb/raddbg_codeview_conversion.c"
#include "raddbg_convert/pdb/raddbg_codeview_stringize.c"
#include "raddbg_convert/pdb/raddbg_pdb_stringize.c"
#include "raddbg_convert/pdb/raddbg_from_pdb.c"
#include "regs/regs.c"
#include "regs/raddbg/regs_raddbg.c"
#include "type_graph/type_graph.c"
#include "dbgi/dbgi.c"
#include "demon/demon_inc.c"
#include "eval/eval_compiler.c"
#include "eval/eval_machine.c"
#include "eval/eval_parser.c"
#include "unwind/unwind.c"
#include "ctrl/ctrl_inc.c"
#include "dasm/dasm.c"
#include "font_provider/font_provider_inc.c"
#include "render/render_inc.c"
#include "texture_cache/texture_cache.c"
#include "geo_cache/geo_cache.c"
#include "font_cache/font_cache.c"
#include "draw/draw.c"
#include "ui/ui_inc.c"
#include "df/df_inc.c"

////////////////////////////////
//~ rjf: Top-Level Execution Types

typedef enum ExecMode
{
  ExecMode_Normal,
  ExecMode_IPCSender,
  ExecMode_Converter,
  ExecMode_Help,
}
ExecMode;

typedef struct IPCInfo IPCInfo;
struct IPCInfo
{
  U64 msg_size;
};

////////////////////////////////
//~ rjf: Top-Level Execution Globals

#define IPC_SHARED_MEMORY_BUFFER_SIZE MB(16)
StaticAssert(IPC_SHARED_MEMORY_BUFFER_SIZE > sizeof(IPCInfo), ipc_buffer_size_requirement);
read_only global String8 ipc_shared_memory_name = str8_lit_comp("_raddbg_ipc_shared_memory_");
read_only global String8 ipc_semaphore_name = str8_lit_comp("_raddbg_ipc_semaphore_");

////////////////////////////////
//~ rjf: Frontend Entry Points

internal void
update_and_render(OS_Handle repaint_window_handle, void *user_data)
{
  ProfTick(0);
  ProfBeginFunction();
  Temp scratch = scratch_begin(0, 0);
  
  //- rjf: tick cache layers
  txt_user_clock_tick();
  geo_user_clock_tick();
  tex_user_clock_tick();
  
  //- rjf: pick delta-time
  // TODO(rjf): maximize, given all windows and their monitors
  // TODO(rjf): also don't be too overly-optimistic, if someone has a 240 Hz display and are consistently missing, don't keep trying at that rate
  F32 dt = 1.f/os_default_refresh_rate();
  
  //- rjf: get events from the OS
  OS_EventList events = {0};
  if(os_handle_match(repaint_window_handle, os_handle_zero()))
  {
    events = os_get_events(scratch.arena, df_gfx_state->num_frames_requested == 0);
  }
  
  //- rjf: bind change
  if(df_gfx_state->bind_change_active)
  {
    if(os_key_press(&events, os_handle_zero(), 0, OS_Key_Esc))
    {
      df_gfx_state->bind_change_active = 0;
    }
    if(os_key_press(&events, os_handle_zero(), 0, OS_Key_Delete))
    {
      df_unbind_spec(df_gfx_state->bind_change_cmd_spec, df_gfx_state->bind_change_binding);
      df_gfx_state->bind_change_active = 0;
      DF_CmdParams p = df_cmd_params_from_gfx();
      df_push_cmd__root(&p, df_cmd_spec_from_core_cmd_kind(df_g_cfg_src_write_cmd_kind_table[DF_CfgSrc_User]));
    }
    for(OS_Event *event = events.first, *next = 0; event != 0; event = next)
    {
      if(event->kind == OS_EventKind_Press &&
         event->key != OS_Key_Esc &&
         event->key != OS_Key_Return &&
         event->key != OS_Key_Backspace &&
         event->key != OS_Key_Delete &&
         event->key != OS_Key_LeftMouseButton &&
         event->key != OS_Key_RightMouseButton &&
         event->key != OS_Key_Ctrl &&
         event->key != OS_Key_Alt &&
         event->key != OS_Key_Shift)
      {
        df_gfx_state->bind_change_active = 0;
        DF_Binding binding = zero_struct;
        {
          binding.key = event->key;
          binding.flags = event->flags;
        }
        df_unbind_spec(df_gfx_state->bind_change_cmd_spec, df_gfx_state->bind_change_binding);
        df_bind_spec(df_gfx_state->bind_change_cmd_spec, binding);
        U32 codepoint = os_codepoint_from_event_flags_and_key(event->flags, event->key);
        os_text(&events, os_handle_zero(), codepoint);
        os_eat_event(&events, event);
        DF_CmdParams p = df_cmd_params_from_gfx();
        df_push_cmd__root(&p, df_cmd_spec_from_core_cmd_kind(df_g_cfg_src_write_cmd_kind_table[DF_CfgSrc_User]));
        break;
      }
    }
  }
  
  //- rjf: take hotkeys
  {
    for(OS_Event *event = events.first, *next = 0;
        event != 0;
        event = next)
    {
      next = event->next;
      DF_Window *window = df_window_from_os_handle(event->window);
      DF_CmdParams params = window ? df_cmd_params_from_window(window) : df_cmd_params_from_gfx();
      if(event->kind == OS_EventKind_Press)
      {
        DF_Binding binding = {event->key, event->flags};
        DF_CmdSpecList spec_candidates = df_cmd_spec_list_from_binding(scratch.arena, binding);
        if(spec_candidates.first != 0 && !df_cmd_spec_is_nil(spec_candidates.first->spec))
        {
          DF_CmdSpec *spec = spec_candidates.first->spec;
          params.cmd_spec = spec;
          df_cmd_params_mark_slot(&params, DF_CmdParamSlot_CmdSpec);
          U32 hit_char = os_codepoint_from_event_flags_and_key(event->flags, event->key);
          os_eat_event(&events, event);
          df_push_cmd__root(&params, df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_CommandFastPath));
          if(event->flags & OS_EventFlag_Alt)
          {
            window->menu_bar_focus_press_started = 0;
          }
        }
        df_gfx_request_frame();
      }
      else if(event->kind == OS_EventKind_Text)
      {
        String32 insertion32 = str32(&event->character, 1);
        String8 insertion8 = str8_from_32(scratch.arena, insertion32);
        DF_CmdSpec *spec = df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_InsertText);
        params.string = insertion8;
        df_cmd_params_mark_slot(&params, DF_CmdParamSlot_String);
        df_push_cmd__root(&params, spec);
        df_gfx_request_frame();
      }
    }
  }
  
  //- rjf: menu bar focus
  {
    for(OS_Event *event = events.first, *next = 0; event != 0; event = next)
    {
      next = event->next;
      DF_Window *ws = df_window_from_os_handle(event->window);
      if(ws == 0)
      {
        continue;
      }
      if(event->kind == OS_EventKind_Press && event->key == OS_Key_Alt && event->is_repeat == 0)
      {
        ws->menu_bar_focused_on_press = ws->menu_bar_focused;
        ws->menu_bar_key_held = 1;
        ws->menu_bar_focus_press_started = 1;
      }
      if(event->kind == OS_EventKind_Release && event->key == OS_Key_Alt && event->is_repeat == 0)
      {
        ws->menu_bar_key_held = 0;
      }
      if(ws->menu_bar_focused && event->kind == OS_EventKind_Press && event->key == OS_Key_Alt && event->is_repeat == 0)
      {
        os_eat_event(&events, event);
        ws->menu_bar_focused = 0;
      }
      else if(ws->menu_bar_focus_press_started && !ws->menu_bar_focused && event->kind == OS_EventKind_Release && event->key == OS_Key_Alt && event->is_repeat == 0)
      {
        os_eat_event(&events, event);
        ws->menu_bar_focused = !ws->menu_bar_focused_on_press;
        ws->menu_bar_focus_press_started = 0;
      }
      else if(event->kind == OS_EventKind_Press && event->key == OS_Key_Esc && ws->menu_bar_focused && !ui_any_ctx_menu_is_open())
      {
        os_eat_event(&events, event);
        ws->menu_bar_focused = 0;
      }
    }
  }
  
  //- rjf: gather root-level commands
  DF_CmdList cmds = df_core_gather_root_cmds(scratch.arena);
  
  //- rjf: begin frame
  df_core_begin_frame(scratch.arena, &cmds, dt);
  df_gfx_begin_frame(scratch.arena, &cmds);
  
  //- rjf: queue drop for drag/drop
  if(df_drag_is_active())
  {
    for(OS_Event *event = events.first; event != 0; event = event->next)
    {
      if(event->kind == OS_EventKind_Release && event->key == OS_Key_LeftMouseButton)
      {
        df_queue_drag_drop();
        break;
      }
    }
  }
  
  //- rjf: auto-focus moused-over windows while dragging
  if(df_drag_is_active())
  {
    B32 over_focused_window = 0;
    {
      for(DF_Window *window = df_gfx_state->first_window; window != 0; window = window->next)
      {
        Vec2F32 mouse = os_mouse_from_window(window->os);
        Rng2F32 rect = os_client_rect_from_window(window->os);
        if(os_window_is_focused(window->os) && contains_2f32(rect, mouse))
        {
          over_focused_window = 1;
          break;
        }
      }
    }
    if(!over_focused_window)
    {
      for(DF_Window *window = df_gfx_state->first_window; window != 0; window = window->next)
      {
        Vec2F32 mouse = os_mouse_from_window(window->os);
        Rng2F32 rect = os_client_rect_from_window(window->os);
        if(!os_window_is_focused(window->os) && contains_2f32(rect, mouse))
        {
          os_window_focus(window->os);
          break;
        }
      }
    }
  }
  
  //- rjf: update & render
  {
    d_begin_frame();
    for(DF_Window *w = df_gfx_state->first_window; w != 0; w = w->next)
    {
      df_window_update_and_render(scratch.arena, &events, w, &cmds);
    }
  }
  
  //- rjf: end frontend frame, send signals, etc.
  df_gfx_end_frame();
  df_core_end_frame();
  
  //- rjf: submit rendering to all windows
  {
    r_begin_frame();
    for(DF_Window *w = df_gfx_state->first_window; w != 0; w = w->next)
    {
      r_window_begin_frame(w->os, w->r);
      d_submit_bucket(w->os, w->r, w->draw_bucket);
      r_window_end_frame(w->os, w->r);
    }
    r_end_frame();
  }
  
  //- rjf: take window closing events
  for(OS_Event *e = events.first; e; e = e->next)
  {
    if(e->kind == OS_EventKind_WindowClose)
    {
      for(DF_Window *w = df_gfx_state->first_window; w != 0; w = w->next)
      {
        if(os_handle_match(w->os, e->window))
        {
          DF_CmdParams params = df_cmd_params_from_window(w);
          df_push_cmd__root(&params, df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_CloseWindow));
          break;
        }
      }
    }
  }
  
  scratch_end(scratch);
  ProfEnd();
}

internal CTRL_WAKEUP_FUNCTION_DEF(wakeup_hook)
{
  os_send_wakeup_event();
}

internal void
entry_point(int argc, char **argv)
{
  Temp scratch = scratch_begin(0, 0);
#if PROFILE_TELEMETRY
  local_persist U8 tm_data[MB(64)];
  tmLoadLibrary(TM_RELEASE);
  tmSetMaxThreadCount(1024);
  tmInitialize(sizeof(tm_data), (char *)tm_data);
#endif
  ThreadName("[main]");
  
  //- rjf: initialize basic dependencies
  os_init(argc, argv);
  
  //- rjf: parse command line arguments
  CmdLine cmdln = cmd_line_from_string_list(scratch.arena, os_get_command_line_arguments());
  ExecMode exec_mode = ExecMode_Normal;
  String8 user_cfg_path = str8_lit("");
  String8 profile_cfg_path = str8_lit("");
  B32 capture = 0;
  B32 auto_run = 0;
  B32 auto_step = 0;
  B32 jit_attach = 0;
  U64 jit_pid = 0;
  U64 jit_code = 0;
  U64 jit_addr = 0;
  {
    if(cmd_line_has_flag(&cmdln, str8_lit("ipc")))
    {
      exec_mode = ExecMode_IPCSender;
    }
    else if(cmd_line_has_flag(&cmdln, str8_lit("convert")))
    {
      exec_mode = ExecMode_Converter;
    }
    else if(cmd_line_has_flag(&cmdln, str8_lit("?")) ||
            cmd_line_has_flag(&cmdln, str8_lit("help")))
    {
      exec_mode = ExecMode_Help;
    }
    user_cfg_path = cmd_line_string(&cmdln, str8_lit("user"));
    profile_cfg_path = cmd_line_string(&cmdln, str8_lit("profile"));
    capture = cmd_line_has_flag(&cmdln, str8_lit("capture"));
    auto_run = cmd_line_has_flag(&cmdln, str8_lit("auto_run"));
    auto_step = cmd_line_has_flag(&cmdln, str8_lit("auto_step"));
    String8 jit_pid_string = {0};
    String8 jit_code_string = {0};
    String8 jit_addr_string = {0};
    jit_pid_string = cmd_line_string(&cmdln, str8_lit("jit_pid"));
    jit_code_string = cmd_line_string(&cmdln, str8_lit("jit_code"));
    jit_addr_string = cmd_line_string(&cmdln, str8_lit("jit_addr"));
    try_u64_from_str8_c_rules(jit_pid_string, &jit_pid);
    try_u64_from_str8_c_rules(jit_code_string, &jit_code);
    try_u64_from_str8_c_rules(jit_addr_string, &jit_addr);
    jit_attach = (jit_addr != 0);
  }
  
  //- rjf: auto-start capture
  if(capture)
  {
    ProfBeginCapture("raddbg");
  }
  
  //- rjf: set default user/profile paths
  {
    String8 user_program_data_path = os_string_from_system_path(scratch.arena, OS_SystemPath_UserProgramData);
    String8 user_data_folder = push_str8f(scratch.arena, "%S/%S", user_program_data_path, str8_lit("raddbg"));
    os_make_directory(user_data_folder);
    if(user_cfg_path.size == 0)
    {
      user_cfg_path = push_str8f(scratch.arena, "%S/default.raddbg_user", user_data_folder);
    }
    if(profile_cfg_path.size == 0)
    {
      profile_cfg_path = push_str8f(scratch.arena, "%S/default.raddbg_profile", user_data_folder);
    }
  }
  
  //- rjf: dispatch to top-level codepath based on execution mode
  switch(exec_mode)
  {
    //- rjf: normal execution
    default:
    case ExecMode_Normal:
    {
      //- rjf: set up shared memory for ipc
      OS_Handle ipc_shared_memory = os_shared_memory_alloc(IPC_SHARED_MEMORY_BUFFER_SIZE, ipc_shared_memory_name);
      void *ipc_shared_memory_base = os_shared_memory_view_open(ipc_shared_memory, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
      OS_Handle ipc_semaphore = os_semaphore_alloc(1, 1, ipc_semaphore_name);
      IPCInfo *ipc_info = (IPCInfo *)ipc_shared_memory_base;
      ipc_info->msg_size = 0;
      
      //- rjf: initialize stuff we depend on
      {
        hs_init();
        txt_init();
        dbgi_init();
        txti_init();
        demon_init();
        ctrl_init(wakeup_hook);
        dasm_init();
        os_graphical_init();
        fp_init();
        r_init();
        tex_init();
        geo_init();
        f_init();
        DF_StateDeltaHistory *hist = df_state_delta_history_alloc();
        df_core_init(user_cfg_path, profile_cfg_path, hist);
        df_gfx_init(update_and_render, hist);
        os_set_cursor(OS_Cursor_Pointer);
      }
      
      //- rjf: setup initial target from command line args
      {
        String8List args = cmdln.inputs;
        if(args.node_count > 0 && args.first->string.size != 0)
        {
          Temp scratch = scratch_begin(0, 0);
          DF_Entity *target = df_entity_alloc(0, df_entity_root(), DF_EntityKind_Target);
          df_entity_equip_b32(target, 1);
          df_entity_equip_cfg_src(target, DF_CfgSrc_CommandLine);
          String8List passthrough_args_list = {0};
          for(String8Node *n = args.first->next; n != 0; n = n->next)
          {
            str8_list_push(scratch.arena, &passthrough_args_list, n->string);
          }
          
          // rjf: equip exe
          if(args.first->string.size != 0)
          {
            DF_Entity *exe = df_entity_alloc(0, target, DF_EntityKind_Executable);
            df_entity_equip_name(0, exe, args.first->string);
          }
          
          // rjf: equip path
          String8 path_part_of_arg = str8_chop_last_slash(args.first->string);
          if(path_part_of_arg.size != 0)
          {
            String8 path = push_str8f(scratch.arena, "%S/", path_part_of_arg);
            DF_Entity *execution_path = df_entity_alloc(0, target, DF_EntityKind_ExecutionPath);
            df_entity_equip_name(0, execution_path, path);
          }
          
          // rjf: equip args
          StringJoin join = {str8_lit(""), str8_lit(" "), str8_lit("")};
          String8 args_str = str8_list_join(scratch.arena, &passthrough_args_list, &join);
          if(args_str.size != 0)
          {
            DF_Entity *args_entity = df_entity_alloc(0, target, DF_EntityKind_Arguments);
            df_entity_equip_name(0, args_entity, args_str);
          }
          scratch_end(scratch);
        }
      }
      
      //- rjf: main application loop
      {
        for(;;)
        {
          //- rjf: get IPC messages & dispatch ui commands from them
          {
            if(os_semaphore_take(ipc_semaphore, max_U64))
            {
              if(ipc_info->msg_size != 0)
              {
                U8 *buffer = (U8 *)(ipc_info+1);
                U64 msg_size = ipc_info->msg_size;
                String8 cmd_string = str8(buffer, msg_size);
                ipc_info->msg_size = 0;
                DF_Window *dst_window = df_gfx_state->first_window;
                for(DF_Window *window = dst_window; window != 0; window = window->next)
                {
                  if(os_window_is_focused(window->os))
                  {
                    dst_window = window;
                    break;
                  }
                }
                if(dst_window != 0)
                {
                  Temp scratch = scratch_begin(0, 0);
                  String8 cmd_spec_string = df_cmd_name_part_from_string(cmd_string);
                  DF_CmdSpec *cmd_spec = df_cmd_spec_from_string(cmd_spec_string);
                  if(!df_cmd_spec_is_nil(cmd_spec))
                  {
                    DF_CmdParams params = df_cmd_params_from_gfx();
                    DF_CtrlCtx ctrl_ctx = df_ctrl_ctx_from_window(dst_window);
                    String8 error = df_cmd_params_apply_spec_query(scratch.arena, &ctrl_ctx, &params, cmd_spec, df_cmd_arg_part_from_string(cmd_string));
                    if(error.size == 0)
                    {
                      df_push_cmd__root(&params, cmd_spec);
                    }
                    else
                    {
                      DF_CmdParams params = df_cmd_params_from_window(dst_window);
                      params.string = error;
                      df_cmd_params_mark_slot(&params, DF_CmdParamSlot_String);
                      df_push_cmd__root(&params, df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_Error));
                    }
                  }
                  scratch_end(scratch);
                }
              }
              os_semaphore_drop(ipc_semaphore);
            }
          }
          
          //- rjf: update & render frame
          OS_Handle repaint_window = {0};
          update_and_render(repaint_window, 0);
          
          //- rjf: auto run
          if(auto_run)
          {
            auto_run = 0;
            DF_CmdParams params = df_cmd_params_from_gfx();
            df_push_cmd__root(&params, df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_LaunchAndRun));
          }
          
          //- rjf: auto step
          if(auto_step)
          {
            auto_step = 0;
            DF_CmdParams params = df_cmd_params_from_gfx();
            df_push_cmd__root(&params, df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_StepInto));
          }
          
          //- rjf: jit attach
          if(jit_attach)
          {
            jit_attach = 0;
            DF_CmdParams params = df_cmd_params_from_gfx();
            df_cmd_params_mark_slot(&params, DF_CmdParamSlot_ID);
            params.id = jit_pid;
            df_push_cmd__root(&params, df_cmd_spec_from_core_cmd_kind(DF_CoreCmdKind_Attach));
          }
          
          //- rjf: quit if no windows are left
          if(df_gfx_state->first_window == 0)
          {
            break;
          }
        }
      }
      
    }break;
    
    //- rjf: inter-process communication message sender
    case ExecMode_IPCSender:
    {
      Temp scratch = scratch_begin(0, 0);
      
      //- rjf: grab ipc shared memory
      OS_Handle ipc_shared_memory = os_shared_memory_open(ipc_shared_memory_name);
      void *ipc_shared_memory_base = os_shared_memory_view_open(ipc_shared_memory, r1u64(0, MB(16)));
      if(ipc_shared_memory_base != 0)
      {
        OS_Handle ipc_semaphore = os_semaphore_open(ipc_semaphore_name);
        IPCInfo *ipc_info = (IPCInfo *)ipc_shared_memory_base;
        if(os_semaphore_take(ipc_semaphore, os_now_microseconds() + Million(6)))
        {
          U8 *buffer = (U8 *)(ipc_info+1);
          U64 buffer_max = IPC_SHARED_MEMORY_BUFFER_SIZE - sizeof(IPCInfo);
          StringJoin join = {str8_lit(""), str8_lit(" "), str8_lit("")};
          String8 msg = str8_list_join(scratch.arena, &cmdln.inputs, &join);
          ipc_info->msg_size = Min(buffer_max, msg.size);
          MemoryCopy(buffer, msg.str, ipc_info->msg_size);
          os_semaphore_drop(ipc_semaphore);
        }
      }
      
      scratch_end(scratch);
    }break;
    
    //- rjf: built-in pdb/dwarf -> raddbg converter mode
    case ExecMode_Converter:
    {
      Temp scratch = scratch_begin(0, 0);
      
      //- rjf: parse arguments
      PDBCONV_Params *params = pdb_convert_params_from_cmd_line(scratch.arena, &cmdln);
      
      //- rjf: open output file
      String8 output_name = push_str8_copy(scratch.arena, params->output_name);
      OS_Handle out_file = os_file_open(OS_AccessFlag_Read|OS_AccessFlag_Write, output_name);
      B32 out_file_is_good = !os_handle_match(out_file, os_handle_zero());
      
      //- rjf: convert
      PDBCONV_Out *out = 0;
      if(out_file_is_good)
      {
        out = pdbconv_convert(scratch.arena, params);
      }
      
      //- rjf: bake file
      if(out != 0 && params->output_name.size > 0)
      {
        String8List baked = {0};
        cons_bake_file(scratch.arena, out->root, &baked);
        U64 off = 0;
        for(String8Node *node = baked.first; node != 0; node = node->next)
        {
          os_file_write(out_file, r1u64(off, off+node->string.size), node->string.str);
          off += node->string.size;
        }
      }
      
      //- rjf: close output file
      os_file_close(out_file);
      
      scratch_end(scratch);
    }break;
    
    //- rjf: help message box
    case ExecMode_Help:
    {
      os_graphical_message(0,
                           str8_lit("The RAD Debugger - Help"),
                           str8_lit("The following options may be used when starting the RAD Debugger from the command line:\n\n"
                                    "--user:<path>\n"
                                    "Use to specify the location of a user file which should be used. User files are used to store settings for users, including window and panel setups, path mapping, and visual settings. If this file does not exist, it will be created as necessary. This file will be autosaved as user-related changes are made.\n\n"
                                    "--profile:<path>\n"
                                    "Use to specify the location of a profile file which should be used. Profile files are used to store settings for users and projects. If this file does not exist, it will be created as necessary. This file will be autosaved as profile-related changes are made.\n\n"
                                    "--auto_step\n"
                                    "This will step into all targets after the debugger initially starts.\n\n"
                                    "--auto_run\n"
                                    "This will run all targets after the debugger initially starts.\n\n"
                                    "--ipc <command>\n"
                                    "This will launch the debugger in the non-graphical IPC mode, which is used to communicate with another running instance of the debugger. The debugger instance will launch, send the specified command, then immediately terminate. This may be used by editors or other programs to control the debugger.\n\n"));
    }break;
  }
  
  scratch_end(scratch);
}

////////////////////////////////
//~ rjf: Low-Level Entry Points

//- rjf: windows
#if OS_WINDOWS

global DWORD g_saved_exception_code = 0;

internal DWORD
win32_exception_filter(DWORD dwExceptionCode)
{
  g_saved_exception_code = dwExceptionCode;
  return EXCEPTION_EXECUTE_HANDLER;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  HANDLE output_handles[3] =
  {
    GetStdHandle(STD_INPUT_HANDLE),
    GetStdHandle(STD_OUTPUT_HANDLE),
    GetStdHandle(STD_ERROR_HANDLE),
  };
  for(U64 idx = 0; idx < ArrayCount(output_handles); idx += 1)
  {
    B32 duplicate = 0;
    for(U64 idx2 = 0; idx2 < idx; idx2 += 1)
    {
      if(output_handles[idx2] == output_handles[idx])
      {
        duplicate = 1;
        break;
      }
    }
    if(duplicate)
    {
      output_handles[idx] = 0;
    }
  }
  for(U64 idx = 0; idx < ArrayCount(output_handles); idx += 1)
  {
    if(output_handles[idx] != 0)
    {
      CloseHandle(output_handles[idx]);
    }
  }
  SetStdHandle(STD_INPUT_HANDLE, 0);
  SetStdHandle(STD_OUTPUT_HANDLE, 0);
  SetStdHandle(STD_ERROR_HANDLE, 0);
  static TCTX main_thread_tctx = {0};
  tctx_init_and_equip(&main_thread_tctx);
  Arena *perm_arena = arena_alloc();
  WCHAR *command_line = GetCommandLineW();
  int argc;
  WCHAR **argv_16 = CommandLineToArgvW(command_line, &argc);
  char **argv = push_array(perm_arena, char *, argc);
  for(int i = 0; i < argc; i += 1)
  {
    String16 arg16 = str16_cstring((U16 *)argv_16[i]);
    String8 arg8 = str8_from_16(perm_arena, arg16);
    argv[i] = (char *)arg8.str;
  }
  __try
  {
    entry_point(argc, argv);
  }
  __except(win32_exception_filter(GetExceptionCode()))
  {
    char buffer[256] = {0};
    raddbg_snprintf(buffer, sizeof(buffer), "A fatal exception (code 0x%x) occurred. The process is terminating.", (U32)g_saved_exception_code);
    os_graphical_message(1, str8_lit("Fatal Exception"), str8_cstring(buffer));
    ExitProcess(1);
  }
  return 0;
}

//- rjf: linux
#elif OS_LINUX

int main(int argument_count, char **arguments)
{
  static TCTX main_thread_tctx = {0};
  tctx_init_and_equip(&main_thread_tctx);
  entry_point(argument_count, arguments);
  return 0;
}

#endif
