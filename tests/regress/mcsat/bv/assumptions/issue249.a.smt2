(set-option :produce-unsat-model-interpolants true)
(set-logic QF_BV)
(declare-fun v0 () (_ BitVec 1))
(push 1)
(assert false)
(check-sat-assuming-model (v0) ((_ bv0 1)))
(get-unsat-model-interpolant)
(pop 1)
(check-sat-assuming-model (v0) ((_ bv0 1)))
(get-unsat-model-interpolant)
