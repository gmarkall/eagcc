/* Generated automatically by the program `genrecog' from the target
   machine description file.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tm_p.h"
#include "function.h"
#include "insn-config.h"
#include "recog.h"
#include "output.h"
#include "flags.h"
#include "hard-reg-set.h"
#include "resource.h"
#include "diagnostic-core.h"
#include "reload.h"
#include "regs.h"
#include "tm-constrs.h"



/* `recog' contains a decision tree that recognizes whether the rtx
   X0 is a valid instruction.

   recog returns -1 if the rtx is not valid.  If the rtx is valid, recog
   returns a nonnegative number which is the insn code number for the
   pattern that matched.  This is the same as the order in the machine
   description of the entry that matched.  This number can be used as an
   index into `insn_data' and other tables.

   The third argument to recog is an optional pointer to an int.  If
   present, recog will accept a pattern if it matches except for missing
   CLOBBER expressions at the end.  In that case, the value pointed to by
   the optional pointer will be set to the number of CLOBBERs that need
   to be added (it should be initialized to zero by the caller).  If it
   is set nonzero, the caller should allocate a PARALLEL of the
   appropriate size, copy the initial entries, and call add_clobbers
   (found in insn-emit.c) to fill in the CLOBBERs.


   The function split_insns returns 0 if the rtl could not
   be split or the split rtl as an INSN list if it can be.

   The function peephole2_insns returns 0 if the rtl could not
   be matched. If there was a match, the new rtl is returned in an INSN list,
   and LAST_INSN will point to the last recognized insn in the old sequence.
*/





static int
recog_1 (rtx x0 ATTRIBUTE_UNUSED,
	rtx insn ATTRIBUTE_UNUSED,
	int *pnum_clobbers ATTRIBUTE_UNUSED)
{
  rtx * const operands ATTRIBUTE_UNUSED = &recog_data.operand[0];
  rtx x1 ATTRIBUTE_UNUSED;
  rtx x2 ATTRIBUTE_UNUSED;
  rtx x3 ATTRIBUTE_UNUSED;
  int tem ATTRIBUTE_UNUSED;

  x1 = XEXP (x0, 0);
  if (GET_MODE (x1) == SImode)
    goto L240;
 L2: ATTRIBUTE_UNUSED_LABEL
  if (GET_CODE (x1) == PC)
    goto L7;
  goto ret0;

 L240: ATTRIBUTE_UNUSED_LABEL
  if (register_operand (x1, SImode))
    {
      operands[0] = x1;
      goto L14;
    }
 L241: ATTRIBUTE_UNUSED_LABEL
  if (memory_operand (x1, SImode))
    {
      operands[0] = x1;
      goto L17;
    }
 L242: ATTRIBUTE_UNUSED_LABEL
  if (register_operand (x1, SImode))
    {
      operands[0] = x1;
      goto L23;
    }
 L243: ATTRIBUTE_UNUSED_LABEL
  if (nonimmediate_operand (x1, SImode))
    {
      operands[0] = x1;
      goto L26;
    }
 L244: ATTRIBUTE_UNUSED_LABEL
  if (register_operand (x1, SImode))
    {
      operands[0] = x1;
      goto L29;
    }
  goto L2;

 L14: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (memory_operand (x1, SImode))
    {
      operands[1] = x1;
      return 4;  /* *load_word */
    }
  if (const_int_operand (x1, SImode))
    {
      operands[1] = x1;
      return 6;  /* *constant_load */
    }
  x1 = XEXP (x0, 0);
  goto L241;

 L17: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (register_operand (x1, SImode))
    {
      operands[1] = x1;
      return 5;  /* *store_word */
    }
  x1 = XEXP (x0, 0);
  goto L242;

 L23: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (symbolic_operand (x1, SImode))
    {
      operands[1] = x1;
      return 7;  /* *symbolic_address_load */
    }
  x1 = XEXP (x0, 0);
  goto L243;

 L26: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (zero_register_operand (x1, SImode))
    {
      operands[1] = x1;
      return 8;  /* IITB_move_zero */
    }
  x1 = XEXP (x0, 0);
  goto L244;

 L29: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (GET_MODE (x1) == SImode)
    goto L246;
 L134: ATTRIBUTE_UNUSED_LABEL
  if (GET_CODE (x1) == CALL)
    goto L135;
  x1 = XEXP (x0, 0);
  goto L2;

 L246: ATTRIBUTE_UNUSED_LABEL
  switch (GET_CODE (x1))
    {
    case PLUS:
      goto L33;
    case ABS:
      goto L38;
    case AND:
      goto L42;
    case DIV:
      goto L47;
    case UDIV:
      goto L52;
    case MOD:
      goto L57;
    case UMOD:
      goto L62;
    case MULT:
      goto L67;
    case NEG:
      goto L79;
    case NOT:
      goto L83;
    case IOR:
      goto L87;
    case XOR:
      goto L92;
    case MINUS:
      goto L97;
    case ASHIFT:
      goto L102;
    case ASHIFTRT:
      goto L107;
    case LSHIFTRT:
      goto L112;
    case REG:
    case SUBREG:
      goto L245;
    default:
      goto L134;
   }
 L245: ATTRIBUTE_UNUSED_LABEL
  if (register_operand (x1, SImode))
    {
      operands[1] = x1;
      return 9;  /* *move_regs */
    }
  goto L134;

 L33: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L34;
    }
  goto L134;

 L34: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 10;  
    }
  goto L134;

 L38: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      return 11;  /* abssi2 */
    }
  goto L134;

 L42: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L43;
    }
  goto L134;

 L43: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 12;  /* andsi3 */
    }
  goto L134;

 L47: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L48;
    }
  goto L134;

 L48: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (general_operand (x2, SImode))
    {
      operands[2] = x2;
      return 13;  /* divsi3 */
    }
  goto L134;

 L52: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L53;
    }
  goto L134;

 L53: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (general_operand (x2, SImode))
    {
      operands[2] = x2;
      return 14;  /* udivsi3 */
    }
  goto L134;

 L57: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L58;
    }
  goto L134;

 L58: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    {
      operands[2] = x2;
      return 15;  /* modsi3 */
    }
  goto L134;

 L62: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L63;
    }
  goto L134;

 L63: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    {
      operands[2] = x2;
      return 16;  /* umodsi3 */
    }
  goto L134;

 L67: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (GET_MODE (x2) == SImode)
    goto L263;
  goto L134;

 L263: ATTRIBUTE_UNUSED_LABEL
  if (GET_CODE (x2) == ZERO_EXTEND)
    goto L73;
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L68;
    }
  goto L134;

 L73: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L74;
    }
  goto L134;

 L74: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_MODE (x2) == SImode
      && GET_CODE (x2) == ZERO_EXTEND)
    goto L75;
  goto L134;

 L75: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (general_operand (x3, SImode))
    {
      operands[2] = x3;
      return 18;  /* umulsi3 */
    }
  goto L134;

 L68: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    {
      operands[2] = x2;
      return 17;  /* mulsi3 */
    }
  goto L134;

 L79: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      return 19;  /* negsi2 */
    }
  goto L134;

 L83: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      return 20;  /* one_cmplsi2 */
    }
  goto L134;

 L87: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L88;
    }
  goto L134;

 L88: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 21;  /* iorsi3 */
    }
  goto L134;

 L92: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L93;
    }
  goto L134;

 L93: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 22;  /* xorsi3 */
    }
  goto L134;

 L97: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L98;
    }
  goto L134;

 L98: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    {
      operands[2] = x2;
      return 23;  /* subsi3 */
    }
  goto L134;

 L102: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L103;
    }
  goto L134;

 L103: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 24;  /* ashlsi3 */
    }
  goto L134;

 L107: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L108;
    }
  goto L134;

 L108: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 25;  /* ashrsi3 */
    }
  goto L134;

 L112: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L113;
    }
  goto L134;

 L113: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (nonmemory_operand (x2, SImode))
    {
      operands[2] = x2;
      return 26;  /* lshrsi3 */
    }
  goto L134;

 L135: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (memory_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L136;
    }
  x1 = XEXP (x0, 0);
  goto L2;

 L136: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (immediate_operand (x2, SImode))
    {
      operands[2] = x2;
      goto L137;
    }
  x1 = XEXP (x0, 0);
  goto L2;

 L137: ATTRIBUTE_UNUSED_LABEL
  if (pnum_clobbers != NULL)
    {
      *pnum_clobbers = 1;
      return 28;  /* call_value */
    }
  x1 = XEXP (x0, 0);
  goto L2;

 L7: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (register_operand (x1, SImode))
    {
      operands[0] = x1;
      return 2;  /* indirect_jump */
    }
  switch (GET_CODE (x1))
    {
    case LABEL_REF:
      goto L4;
    case IF_THEN_ELSE:
      goto L141;
    default:
     break;
   }
  goto ret0;

 L4: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  operands[0] = x2;
  return 1;  /* jump */

 L141: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (GET_MODE (x2) == SImode)
    goto L264;
  goto ret0;

 L264: ATTRIBUTE_UNUSED_LABEL
  switch (GET_CODE (x2))
    {
    case LT:
      goto L142;
    case LTU:
      goto L151;
    case EQ:
      goto L160;
    case GE:
      goto L169;
    case GEU:
      goto L178;
    case GT:
      goto L187;
    case GTU:
      goto L196;
    case LE:
      goto L205;
    case LEU:
      goto L214;
    case NE:
      goto L223;
    default:
     break;
   }
 L274: ATTRIBUTE_UNUSED_LABEL
  if (comparison_operator (x2, SImode))
    {
      operands[0] = x2;
      goto L232;
    }
  goto ret0;

 L142: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L143;
    }
  goto L274;

 L143: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L144;
    }
  goto L274;

 L144: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L145;
  x2 = XEXP (x1, 0);
  goto L274;

 L145: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L146;

 L146: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 29;  /* *insn_blt */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L151: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L152;
    }
  goto L274;

 L152: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L153;
    }
  goto L274;

 L153: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L154;
  x2 = XEXP (x1, 0);
  goto L274;

 L154: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L155;

 L155: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 30;  /* *insn_bltu */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L160: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L161;
    }
  goto L274;

 L161: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L162;
    }
  goto L274;

 L162: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L163;
  x2 = XEXP (x1, 0);
  goto L274;

 L163: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L164;

 L164: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 31;  /* *insn_beq */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L169: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L170;
    }
  goto L274;

 L170: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L171;
    }
  goto L274;

 L171: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L172;
  x2 = XEXP (x1, 0);
  goto L274;

 L172: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L173;

 L173: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 32;  /* *insn_bge */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L178: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L179;
    }
  goto L274;

 L179: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L180;
    }
  goto L274;

 L180: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L181;
  x2 = XEXP (x1, 0);
  goto L274;

 L181: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L182;

 L182: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 33;  /* *insn_bgeu */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L187: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L188;
    }
  goto L274;

 L188: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L189;
    }
  goto L274;

 L189: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L190;
  x2 = XEXP (x1, 0);
  goto L274;

 L190: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L191;

 L191: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 34;  /* *insn_bgt */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L196: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L197;
    }
  goto L274;

 L197: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L198;
    }
  goto L274;

 L198: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L199;
  x2 = XEXP (x1, 0);
  goto L274;

 L199: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L200;

 L200: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 35;  /* *insn_bgtu */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L205: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L206;
    }
  goto L274;

 L206: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L207;
    }
  goto L274;

 L207: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L208;
  x2 = XEXP (x1, 0);
  goto L274;

 L208: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L209;

 L209: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 36;  /* *insn_ble */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L214: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L215;
    }
  goto L274;

 L215: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L216;
    }
  goto L274;

 L216: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L217;
  x2 = XEXP (x1, 0);
  goto L274;

 L217: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L218;

 L218: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 37;  /* *insn_bleu */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L223: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L224;
    }
  goto L274;

 L224: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L225;
    }
  goto L274;

 L225: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L226;
  x2 = XEXP (x1, 0);
  goto L274;

 L226: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[0] = x3;
  goto L227;

 L227: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 38;  /* *insn_bne */
    }
  x2 = XEXP (x1, 0);
  goto L274;

 L232: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (register_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L233;
    }
  goto ret0;

 L233: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (register_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L234;
    }
  goto ret0;

 L234: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF)
    goto L235;
  goto ret0;

 L235: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  operands[3] = x3;
  goto L236;

 L236: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == PC)
    {
      return 39;  /* cbranchsi4 */
    }
  goto ret0;
 ret0:
  return -1;
}

int
recog (rtx x0 ATTRIBUTE_UNUSED,
	rtx insn ATTRIBUTE_UNUSED,
	int *pnum_clobbers ATTRIBUTE_UNUSED)
{
  rtx * const operands ATTRIBUTE_UNUSED = &recog_data.operand[0];
  rtx x1 ATTRIBUTE_UNUSED;
  rtx x2 ATTRIBUTE_UNUSED;
  rtx x3 ATTRIBUTE_UNUSED;
  int tem ATTRIBUTE_UNUSED;
  recog_data.insn = NULL_RTX;

  if (GET_MODE (x0) == SImode
      && GET_CODE (x0) == REG
      && XINT (x0, 0) == 0)
    {
      return 0;  /* dummy_pattern */
    }
  switch (GET_CODE (x0))
    {
    case SET:
      goto L13;
    case PARALLEL:
      goto L238;
    case CALL:
      goto L121;
    case CONST_INT:
      goto L239;
    default:
     break;
   }
  goto ret0;

 L13: ATTRIBUTE_UNUSED_LABEL
  return recog_1 (x0, insn, pnum_clobbers);

 L238: ATTRIBUTE_UNUSED_LABEL
  if (XVECLEN (x0, 0) == 2)
    goto L9;
  goto ret0;

 L9: ATTRIBUTE_UNUSED_LABEL
  x1 = XVECEXP (x0, 0, 0);
  switch (GET_CODE (x1))
    {
    case RETURN:
      goto L10;
    case CALL:
      goto L116;
    case SET:
      goto L126;
    default:
     break;
   }
  goto ret0;

 L10: ATTRIBUTE_UNUSED_LABEL
  x1 = XVECEXP (x0, 0, 1);
  if (GET_CODE (x1) == USE)
    goto L11;
  goto ret0;

 L11: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (GET_MODE (x2) == SImode
      && GET_CODE (x2) == REG
      && XINT (x2, 0) == 31)
    {
      return 3;  /* IITB_return */
    }
  goto ret0;

 L116: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (memory_operand (x2, SImode))
    {
      operands[0] = x2;
      goto L117;
    }
  goto ret0;

 L117: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (immediate_operand (x2, SImode))
    {
      operands[1] = x2;
      goto L118;
    }
  goto ret0;

 L118: ATTRIBUTE_UNUSED_LABEL
  x1 = XVECEXP (x0, 0, 1);
  if (GET_CODE (x1) == CLOBBER)
    goto L119;
  goto ret0;

 L119: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (GET_MODE (x2) == SImode
      && GET_CODE (x2) == REG
      && XINT (x2, 0) == 31)
    {
      return 27;  /* call */
    }
  goto ret0;

 L126: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    {
      operands[0] = x2;
      goto L127;
    }
  goto ret0;

 L127: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == CALL)
    goto L128;
  goto ret0;

 L128: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 0);
  if (memory_operand (x3, SImode))
    {
      operands[1] = x3;
      goto L129;
    }
  goto ret0;

 L129: ATTRIBUTE_UNUSED_LABEL
  x3 = XEXP (x2, 1);
  if (immediate_operand (x3, SImode))
    {
      operands[2] = x3;
      goto L130;
    }
  goto ret0;

 L130: ATTRIBUTE_UNUSED_LABEL
  x1 = XVECEXP (x0, 0, 1);
  if (GET_CODE (x1) == CLOBBER)
    goto L131;
  goto ret0;

 L131: ATTRIBUTE_UNUSED_LABEL
  x2 = XEXP (x1, 0);
  if (GET_MODE (x2) == SImode
      && GET_CODE (x2) == REG
      && XINT (x2, 0) == 31)
    {
      return 28;  /* call_value */
    }
  goto ret0;

 L121: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 0);
  if (memory_operand (x1, SImode))
    {
      operands[0] = x1;
      goto L122;
    }
  goto ret0;

 L122: ATTRIBUTE_UNUSED_LABEL
  x1 = XEXP (x0, 1);
  if (immediate_operand (x1, SImode))
    {
      operands[1] = x1;
      goto L123;
    }
  goto ret0;

 L123: ATTRIBUTE_UNUSED_LABEL
  if (pnum_clobbers != NULL)
    {
      *pnum_clobbers = 1;
      return 27;  /* call */
    }
  goto ret0;

 L239: ATTRIBUTE_UNUSED_LABEL
  if (XWINT (x0, 0) == 0L)
    {
      return 40;  /* nop */
    }
  goto ret0;
 ret0:
  return -1;
}

rtx
split_insns (rtx x0 ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
  rtx * const operands ATTRIBUTE_UNUSED = &recog_data.operand[0];
  rtx x1 ATTRIBUTE_UNUSED;
  rtx x2 ATTRIBUTE_UNUSED;
  rtx x3 ATTRIBUTE_UNUSED;
  rtx tem ATTRIBUTE_UNUSED;
  recog_data.insn = NULL_RTX;
  goto ret0;
 ret0:
  return 0;
}

