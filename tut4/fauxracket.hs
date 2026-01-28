data Expr = Lit Integer | Bin Op Expr Expr
data Op = Add | Mult

-- Comment should be: (Bin Add (Lit 1) (Bin Mult (Lit 2) (Lit 3)))
-- Note: Bin takes exactly 3 args: Op, Expr, Expr

interp :: Expr -> Integer  -- Use :: not : for type signatures
interp (Lit x) = x
interp (Bin Add a b) = (interp a) + (interp b)
interp (Bin Mult a b) = (interp a) * (interp b)
