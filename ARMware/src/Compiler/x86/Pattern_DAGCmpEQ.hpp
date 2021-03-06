// ARMware - an ARM emulator
// Copyright (C) <2007>  Wei Hu <wei.hu.tw@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef Pattern_DAGCmpEQ_hpp
#define Pattern_DAGCmpEQ_hpp

#if ENABLE_DYNAMIC_TRANSLATOR

namespace ARMware
{
  namespace Pattern_DAGCmpEQ
  {
    inline void
    emit_lir_code(BasicBlock * const curr_bb, DAGNode * const node)
    {
      assert(DAG_CMP_EQ == node->kind());
      
      assert(0 == (node->in_flags() | node->out_flags()));
      assert(0 == node->attached_var_amount());
      
      std::deque<ChildInfo> const &children = node->children();
      
      ChildInfo const &child_0 = children.front();
      ChildInfo const &child_1 = children.back();
      
      switch (child_0.node()->kind())
      {
      case DAG_VAR_CONST:
        switch (child_1.node()->kind())
        {
        case DAG_VAR_CONST:
          assert(!"The 1st operand of the CMP instruction in x86 can't be a constant value.");
          break;
          
        case DAG_VAR_TEMP:
        case DAG_VAR_GLOBAL:
          assert(!"The 1st operand of the CMP instruction in x86 can't be a constant value.");
          break;
          
        default:
          assert(!"The 1st operand of the CMP instruction in x86 can't be a constant value.");
          break;
        }
        break;
        
      case DAG_VAR_TEMP:
      case DAG_VAR_GLOBAL:
        switch (child_1.node()->kind())
        {
        case DAG_VAR_CONST:
          curr_bb->append_lir<true>(new LIR(static_cast<LIRCmp *>(0),
                                            child_0.peek_first_usable_attached_var(),
                                            child_1.peek_first_usable_attached_var()->const_num()));
          break;
          
        case DAG_VAR_TEMP:
        case DAG_VAR_GLOBAL:
          curr_bb->append_lir<true>(new LIR(static_cast<LIRCmp *>(0),
                                            child_0.peek_first_usable_attached_var(),
                                            child_1.peek_first_usable_attached_var()));
          break;
          
        default:
          curr_bb->append_lir<true>(new LIR(static_cast<LIRCmp *>(0),
                                            child_0.peek_first_usable_attached_var(),
                                            child_1.peek_first_usable_attached_var()));
          break;
        }
        break;
        
      default:
        switch (child_1.node()->kind())
        {
        case DAG_VAR_CONST:
          curr_bb->append_lir<true>(new LIR(static_cast<LIRCmp *>(0),
                                            child_0.peek_first_usable_attached_var(),
                                            child_1.peek_first_usable_attached_var()->const_num()));
          break;
          
        case DAG_VAR_TEMP:
        case DAG_VAR_GLOBAL:
          curr_bb->append_lir<true>(new LIR(static_cast<LIRCmp *>(0),
                                            child_1.peek_first_usable_attached_var(),
                                            child_0.peek_first_usable_attached_var()));
          break;
          
        default:
          curr_bb->append_lir<true>(new LIR(static_cast<LIRCmp *>(0),
                                            child_0.peek_first_usable_attached_var(),
                                            child_1.peek_first_usable_attached_var()));
          break;
        }
        break;
      }
      
      curr_bb->append_lir<true>(new LIR(static_cast<LIRJz *>(0), node->label()));
    }
  }
}

#endif

#endif
