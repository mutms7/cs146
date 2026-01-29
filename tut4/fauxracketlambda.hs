data Expr = Fun String Expr
          | App Expr Expr
          | With (String, Expr) Expr
          | Var String
          | Lit Integer
          | Bin Op Expr Expr
          deriving Show

data Op = Add | Sub | Mult | Div
          deriving Show

interp :: Expr -> Expr
interp x@(Lit _) = x
interp x@(Var _) = x
interp x@(Fun _ _) = x
interp (With (var, val) body) = interp (App (Fun var body) val)
interp (App fn arg) = interp (subst par (interp arg) body)
    where (Fun par body) = interp fn
interp (Bin op a b) = Lit (applyOp op a' b')
    where
        (Lit a') = interp a
        (Lit b') = interp b

applyOp :: Op -> Integer -> Integer -> Integer
applyOp Add a b = a + b
applyOp Sub a b = a - b
applyOp Mult a b = a * b
applyOp Div a b = a `div` b

subst :: String -> Expr -> Expr -> Expr
subst i v (Var x) = if x == i then v else (Var x)  -- compare strings, not to 1
subst i v (Lit x) = Lit x
subst i v (Bin op a b) = Bin op (subst i v a) (subst i v b)
subst i v (Fun param body) = Fun param (subst i v body)  -- missing case!
subst i v (App f a) = App (subst i v f) (subst i v a)    -- missing case!
subst i v (With p body) = With p (subst i v body)        -- missing case!