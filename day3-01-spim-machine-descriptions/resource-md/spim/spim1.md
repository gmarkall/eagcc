;; The dummy instruction has been supported to ensure that no empty
;; arrays are generated in source files of the generated compiler in the
;; initial levels..

(define_insn "dummy_pattern"
        [(reg:SI 0)]
        "1"
        "This stmnt should not be emitted!"
)

;; Functions in genemit.c read .md file for desired target and generates
;; gen_<insn-name> function  for each standard named  pattern defined in
;; .md file.  The function gen_<insn-name>  is in turn used  to generate
;; RTLs at the  time of transforming input program into  RTL. The source
;; files  cfgrtl.c,  cse.c,expmed.c which  contribute  in  cc1, use  the
;; function gen_jump to generate insn corresponding to jump instruction.
;; If this pattern is not  defined in machine description, the compiler,
;; fails in the linking phase because gen_jump is not defined.


;; For compiling _any_ program, jumps are a must.

(define_insn "jump"
        [(set (pc) (label_ref (match_operand 0 "" "")))]
        ""
	{
                return "*j \\t%l0";
        }
)

(define_insn "indirect_jump"
	[(set (pc) (match_operand:SI 0 "register_operand" ""))]
	""
	"jr \\t%0"
)

(define_expand "epilogue"
        [(clobber (const_int 0))]
        ""
        {
                spim_epilogue();
                DONE;
        }
)

(define_insn "IITB_return"
	[(return)
	 (use (reg:SI 31))]
	""
	"jr \\t\\$ra"
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This is the basic standard named pattern, which is matched at the time of 
;; GIMPLE to RTL conversion. Hence to add assignment operation in our machine
;; description, we have to define this standard pattern. We can have various
;; variants of this pattern depending upon which target instruction to emit,
;; and move patterns supported in the architecture. These variants can be
;; defined using define_insn patterns and constraints handling specific 
;; pattern.

;;movmisalignm is to be used for unaligned memory boundaries.

(define_expand "movsi"
	[(set (match_operand:SI 0 "nonimmediate_operand" "")
	      (match_operand:SI 1 "general_operand" "")
	)]
""
{

	  if(GET_CODE(operands[1])==CONST_INT && INTVAL(operands[1])==0)
	  {
	    emit_insn(gen_IITB_move_zero(operands[0],gen_rtx_REG(SImode,0)));
	    DONE;
  	  }
	  
	  if(GET_CODE(operands[0])==MEM && GET_CODE(operands[1])!=REG)
	  {
	    
	    if(can_create_pseudo_p())
	    {
		operands[1]=force_reg(SImode,operands[1]);
	    }
  }
}
)


;;Load patterns

(define_insn "*load_word"
	[(set (match_operand:SI 0 "register_operand" "=r")
	      (match_operand:SI 1 "memory_operand" "m")
	)]
	""
	"lw \\t%0, %m1"
)

;;store patterns

(define_insn "*store_word"
	[(set (match_operand:SI 0 "memory_operand" "=m")
	      (match_operand:SI 1 "register_operand" "r")
	)]
	""
	"sw \\t%1, %m0"
)

;;Constant loads

(define_insn "*constant_load"
	[(set (match_operand:SI 0 "register_operand" "=r")
	      (match_operand:SI 1 "const_int_operand" "i"))]
	""
	"li \\t%0, %c1"
;; This can also be defined using the actual lui instruction along with shift insn, 
;; but that will be used once shift operation is included in md file.
)

(define_insn "*symbolic_address_load" 
	[(set (match_operand:SI 0 "register_operand" "=r")
	      (match_operand:SI 1 "symbolic_operand" "S"))]
	""
	"la \\t%0, %s1"
)

;; Here z is the constraint character defined in REG_CLASS_FROM_LETTER_P
;; The register $zero is used here. 

(define_insn "IITB_move_zero"
	[(set (match_operand:SI 0 "nonimmediate_operand" "=r,m")
	      (match_operand:SI 1 "zero_register_operand" "z,z")
	)]
	""
	"@
	move \\t%0,%1
	sw \\t%1, %m0"
)

(define_insn "*move_regs"
      [(set (match_operand:SI 0 "register_operand" "=r")
              (match_operand:SI 1 "register_operand" "r")
       )]
        ""
        "move \\t%0,%1"
)

(define_insn "addsi3"
	[(set (match_operand:SI 0 "register_operand" "=r,r")
              (plus:SI (match_operand:SI 1 "register_operand" "r,r")
                       (match_operand:SI 2 "nonmemory_operand" "r,K"))
         )]
        ""
        "@
         add \\t%0, %1, %2
         addi \\t%0, %1, %c2"

)

(define_expand "prologue"
	[(clobber (const_int 0))]
	""
	{
		spim_prologue();
		DONE;
	}
)

;;isha added
(define_insn "nop"
  [(const_int 0)]
  ""
  "nop"
)

