(set-logic QF_BV)
(declare-fun _substvar_102_ () (_ BitVec 5))
(declare-fun _substvar_52_ () (_ BitVec 5))
(declare-fun _substvar_92_ () (_ BitVec 5))
(declare-fun _substvar_98_ () (_ BitVec 5))
(declare-fun _substvar_49_ () (_ BitVec 5))
(declare-fun _substvar_54_ () (_ BitVec 5))
(declare-fun _substvar_93_ () (_ BitVec 5))
(assert (= _substvar_49_ (_ bv0 5)))
(assert (bvsle _substvar_54_ (_ bv2 5)))
(assert (bvsle _substvar_52_ (_ bv2 5)))
(assert (= (bvadd (bvmul _substvar_98_ _substvar_52_) (bvadd (_ bv0 5) (bvadd _substvar_92_ (_ bv0 5)))) (_ bv0 5)))
(assert (bvsle (_ bv30 5) _substvar_98_))
(assert (bvsle _substvar_102_ (_ bv2 5)))
(assert (bvsle (_ bv1 5) _substvar_102_))
(assert (= (bvadd _substvar_102_ (bvadd (_ bv0 5) (bvadd (bvmul (_ bv31 5) (bvmul _substvar_93_ _substvar_52_)) (bvadd (_ bv0 5) (bvmul (_ bv31 5) _substvar_92_))))) (_ bv0 5)))
(assert (= (bvadd (bvmul (_ bv30 5) (bvmul _substvar_98_ _substvar_52_)) (_ bv0 5)) (_ bv0 5)))
(check-sat)
(exit)
