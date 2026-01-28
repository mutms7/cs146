data Lst = Empty | Cons Integer Lst deriving Show
data Glist a = GEmpty | GCons a (Glist a) deriving Show
mylen :: Lst -> Integer
mylen Empty = 0
mylen (Cons x rest) = 1 + (mylen rest)

mylenG :: (Glist a) -> Integer
mylenG GEmpty = 0
mylenG(GCons _ rest) = 1 + (mylenG rest)