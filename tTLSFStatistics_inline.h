# i f n d e f   t T L S F S t a t i s t i c s _ _ I N L I N E _ H 
 # d e f i n e   t T L S F S t a t i s t i c s _ _ I N L I N E _ H 
 
 # i n c l u d e   " t _ s y s l o g . h " 
 
 / * 
   *   S0n0󤕘񍲄o0  t e c s g e n   k0�0�0򶙄󪪶�0�0h0W0f0陙誖ubU0�0~0W0_0
   *   S0n0󤕘񍲄�0鑮茤W0f0O(uY0�0S0h0L0a骎U0�0f0D0~0Y0L0
   *   t e c s g e n   n0峇焄L坘0�0�0
N鴉M0U0�0f0W0~0F0_0�00�8^
   *       g e n / t T L S F S t a t i s t i c s _ t e m p l a t e . c   = >   s r c / t T L S F S t a t i s t i c s . c 
   *   n0�0F0k0TMR,   󤖨�0򣬪	Y鬴W0f0K0�0頞ckW0~0Y0
   * / 
 / *   # [ < P R E A M B L E > ] # 
   *   # [ < . . . > ] #   K0�0  # [ < / . . . > ] #   g0騐~0�0_0񻹨�0�0o0鑮茤W0j0D0g0O0`0U0D0
   *   t e c s m e r g e   k0�0�0􀏞�0k0O(uU0�0~0Y0
   * 
   *   |Ts0鉙pe  # _ T C P F _ # 
   *   r e q u i r e   p o r t :   s i g n a t u r e : s K e r n e l   c o n t e x t : t a s k 
   *       E R                           s l e e p (   ) ; 
   *       E R                           s l e e p T i m e o u t (   T M O   t i m e o u t   ) ; 
   *       E R                           d e l a y (   R E L T I M   d e l a y T i m e   ) ; 
   *       E R                           e x i t T a s k (   ) ; 
   *       E R                           g e t T a s k I d (   I D *   p _ t a s k I d   ) ; 
   *       E R                           r o t a t e R e a d y Q u e u e (   P R I   t a s k P r i o r i t y   ) ; 
   *       E R                           g e t T i m e (   S Y S T I M *   p _ s y s t e m T i m e   ) ; 
   *       E R                           g e t M i c r o T i m e (   S Y S U T M *   p _ s y s t e m M i c r o T i m e   ) ; 
   *       E R                           l o c k C p u (   ) ; 
   *       E R                           u n l o c k C p u (   ) ; 
   *       E R                           d i s a b l e D i s p a t c h (   ) ; 
   *       E R                           e n a b l e D i s p a t c h (   ) ; 
   *       E R                           d i s a b l e T a s k E x c e p t i o n (   ) ; 
   *       E R                           e n a b l e T a s k E x c e p t i o n (   ) ; 
   *       E R                           c h a n g e I n t e r r u p t P r i o r i t y M a s k (   P R I   i n t e r r u p t P r i o r i t y   ) ; 
   *       E R                           g e t I n t e r r u p t P r i o r i t y M a s k (   P R I *   p _ i n t e r r u p t P r i o r i t y   ) ; 
   *       E R                           e x i t K e r n e l (   ) ; 
   *       b o o l _ t                   s e n s e C o n t e x t (   ) ; 
   *       b o o l _ t                   s e n s e L o c k (   ) ; 
   *       b o o l _ t                   s e n s e D i s p a t c h (   ) ; 
   *       b o o l _ t                   s e n s e D i s p a t c h P e n d i n g S t a t e (   ) ; 
   *       b o o l _ t                   s e n s e K e r n e l (   ) ; 
   *   c a l l   p o r t :   c M a l l o c   s i g n a t u r e :   s M a l l o c   c o n t e x t : t a s k 
   *       i n t                         c M a l l o c _ i n i t i a l i z e M e m o r y P o o l (   ) ; 
   *       v o i d *                     c M a l l o c _ c a l l o c (   s i z e _ t   n e l e m ,   s i z e _ t   e l e m _ s i z e   ) ; 
   *       v o i d *                     c M a l l o c _ m a l l o c (   s i z e _ t   s i z e   ) ; 
   *       v o i d *                     c M a l l o c _ r e a l l o c (   c o n s t   v o i d *   p t r ,   s i z e _ t   n e w _ s i z e   ) ; 
   *       v o i d                       c M a l l o c _ f r e e (   c o n s t   v o i d *   p t r   ) ; 
   *   c a l l   p o r t :   c M a l l o c S t a t i s t i c s   s i g n a t u r e :   s M a l l o c S t a t i s t i c s   c o n t e x t : t a s k 
   *       s i z e _ t                   c M a l l o c S t a t i s t i c s _ g e t U s e d S i z e (   ) ; 
   *       s i z e _ t                   c M a l l o c S t a t i s t i c s _ g e t M a x S i z e (   ) ; 
   * 
   *   # [ < / P R E A M B L E > ] #   * / 
 
 # i f d e f   S E Q U E N T I A L 
 e x t e r n   S Y S T I M   s t a r t _ t i m e ; 
 # e n d i f 
 
 / *   譙Q0鉙pe  # _ T E P F _ #   * / 
 / *   # [ < E N T R Y _ P O R T > ] #   e M a l l o c 
   *   e n t r y   p o r t :   e M a l l o c 
   *   s i g n a t u r e :     s M a l l o c 
   *   c o n t e x t :         t a s k 
   *   # [ < / E N T R Y _ P O R T > ] #   * / 
 
 / *   # [ < E N T R Y _ F U N C > ] #   e M a l l o c _ i n i t i a l i z e M e m o r y P o o l 
   *   n a m e :                   e M a l l o c _ i n i t i a l i z e M e m o r y P o o l 
   *   g l o b a l _ n a m e :     t T L S F S t a t i s t i c s _ e M a l l o c _ i n i t i a l i z e M e m o r y P o o l 
   *   o n e w a y :               f a l s e 
   *   # [ < / E N T R Y _ F U N C > ] #   * / 
 I n l i n e   i n t 
 e M a l l o c _ i n i t i a l i z e M e m o r y P o o l ( C E L L I D X   i d x ) 
 { 
 	 C E L L C B 	 * p _ c e l l c b ; 
 	 i f   ( V A L I D _ I D X ( i d x ) )   { 
 	 	 p _ c e l l c b   =   G E T _ C E L L C B ( i d x ) ; 
 	 } 
 	 e l s e   { 
 	 }   / *   e n d   i f   V A L I D _ I D X ( i d x )   * / 
 
     	 r e t u r n   c M a l l o c _ i n i t i a l i z e M e m o r y P o o l ( ) ; 
 } 
 
 / *   # [ < E N T R Y _ F U N C > ] #   e M a l l o c _ c a l l o c 
   *   n a m e :                   e M a l l o c _ c a l l o c 
   *   g l o b a l _ n a m e :     t T L S F S t a t i s t i c s _ e M a l l o c _ c a l l o c 
   *   o n e w a y :               f a l s e 
   *   # [ < / E N T R Y _ F U N C > ] #   * / 
 I n l i n e   v o i d * 
 e M a l l o c _ c a l l o c ( C E L L I D X   i d x ,   s i z e _ t   n e l e m ,   s i z e _ t   e l e m _ s i z e ) 
 { 
 	 C E L L C B 	 * p _ c e l l c b ; 
 	 i f   ( V A L I D _ I D X ( i d x ) )   { 
 	 	 p _ c e l l c b   =   G E T _ C E L L C B ( i d x ) ; 
 	 } 
 	 e l s e   { 
 	 }   / *   e n d   i f   V A L I D _ I D X ( i d x )   * / 
 
         v o i d   * r e t ; 
 # i f d e f   S E Q U E N T I A L 
 	 S Y S T I M   n o w _ t i m e ; 
 	 g e t T i m e ( & n o w _ t i m e ) ; 
 # e n d i f 
         r e t   =   c M a l l o c _ c a l l o c ( n e l e m ,   e l e m _ s i z e ) ; 
 # i f d e f   S E Q U E N T I A L 
         s y s l o g ( L O G _ E M E R G ,   " [ T L S F ]   % d   m s   | |   c a l l o c :   % d   b y t e s ,   t o t a l :   % d   b y t e s " , 
         	 	 n o w _ t i m e   -   s t a r t _ t i m e ,   n e l e m   *   e l e m _ s i z e ,   c M a l l o c S t a t i s t i c s _ g e t U s e d S i z e ( ) ) ; 
 # e n d i f 
         r e t u r n   r e t ; 
 } 
 
 / *   # [ < E N T R Y _ F U N C > ] #   e M a l l o c _ m a l l o c 
   *   n a m e :                   e M a l l o c _ m a l l o c 
   *   g l o b a l _ n a m e :     t T L S F S t a t i s t i c s _ e M a l l o c _ m a l l o c 
   *   o n e w a y :               f a l s e 
   *   # [ < / E N T R Y _ F U N C > ] #   * / 
 I n l i n e   v o i d * 
 e M a l l o c _ m a l l o c ( C E L L I D X   i d x ,   s i z e _ t   s i z e ) 
 { 
 	 C E L L C B 	 * p _ c e l l c b ; 
 	 i f   ( V A L I D _ I D X ( i d x ) )   { 
 	 	 p _ c e l l c b   =   G E T _ C E L L C B ( i d x ) ; 
 	 } 
 	 e l s e   { 
 	 }   / *   e n d   i f   V A L I D _ I D X ( i d x )   * / 
 
 	 v o i d   * r e t ; 
 # i f d e f   S E Q U E N T I A L 
 	 S Y S T I M   n o w _ t i m e ; 
 	 g e t T i m e ( & n o w _ t i m e ) ; 
 # e n d i f 
 	 r e t   =   c M a l l o c _ m a l l o c ( s i z e ) ; 
 # i f d e f   S E Q U E N T I A L 
 	 s y s l o g ( L O G _ E M E R G ,   " [ T L S F ]   % d   m s   | |   m a l l o c :   % d   b y t e s ,   t o t a l :   % d   b y t e s " , 
 	 	 	 n o w _ t i m e   -   s t a r t _ t i m e ,   s i z e ,   c M a l l o c S t a t i s t i c s _ g e t U s e d S i z e ( ) ) ; 
 # e n d i f 
         r e t u r n   r e t ; 
 } 
 
 / *   # [ < E N T R Y _ F U N C > ] #   e M a l l o c _ r e a l l o c 
   *   n a m e :                   e M a l l o c _ r e a l l o c 
   *   g l o b a l _ n a m e :     t T L S F S t a t i s t i c s _ e M a l l o c _ r e a l l o c 
   *   o n e w a y :               f a l s e 
   *   # [ < / E N T R Y _ F U N C > ] #   * / 
 I n l i n e   v o i d * 
 e M a l l o c _ r e a l l o c ( C E L L I D X   i d x ,   c o n s t   v o i d *   p t r ,   s i z e _ t   n e w _ s i z e ) 
 { 
 	 C E L L C B 	 * p _ c e l l c b ; 
 	 i f   ( V A L I D _ I D X ( i d x ) )   { 
 	 	 p _ c e l l c b   =   G E T _ C E L L C B ( i d x ) ; 
 	 } 
 	 e l s e   { 
 	 }   / *   e n d   i f   V A L I D _ I D X ( i d x )   * / 
 
 	 v o i d   * r e t ; 
 # i f d e f   S E Q U E N T I A L 
 	 S Y S T I M   n o w _ t i m e ; 
 	 g e t T i m e ( & n o w _ t i m e ) ; 
 # e n d i f 
 	 r e t   =   c M a l l o c _ r e a l l o c ( p t r ,   n e w _ s i z e ) ; 
 # i f d e f   S E Q U E N T I A L 
 	 s y s l o g ( L O G _ E M E R G ,   " [ T L S F ]   % d   m s   | |   r e a l l o c :   % d   b y t e s ,   t o t a l :   % d   b y t e s " , 
 	 	 	 n o w _ t i m e   -   s t a r t _ t i m e ,   n e w _ s i z e ,   c M a l l o c S t a t i s t i c s _ g e t U s e d S i z e ( ) ) ; 
 # e n d i f 
         r e t u r n   r e t ; 
 } 
 
 / *   # [ < E N T R Y _ F U N C > ] #   e M a l l o c _ f r e e 
   *   n a m e :                   e M a l l o c _ f r e e 
   *   g l o b a l _ n a m e :     t T L S F S t a t i s t i c s _ e M a l l o c _ f r e e 
   *   o n e w a y :               f a l s e 
   *   # [ < / E N T R Y _ F U N C > ] #   * / 
 I n l i n e   v o i d 
 e M a l l o c _ f r e e ( C E L L I D X   i d x ,   c o n s t   v o i d *   p t r ) 
 { 
 	 C E L L C B 	 * p _ c e l l c b ; 
 	 i f   ( V A L I D _ I D X ( i d x ) )   { 
 	 	 p _ c e l l c b   =   G E T _ C E L L C B ( i d x ) ; 
 	 } 
 	 e l s e   { 
 	 }   / *   e n d   i f   V A L I D _ I D X ( i d x )   * / 
 
 # i f d e f   S E Q U E N T I A L 
 	 S Y S T I M   n o w _ t i m e ; 
 	 g e t T i m e ( & n o w _ t i m e ) ; 
 # e n d i f 
 	 c M a l l o c _ f r e e ( p t r ) ; 
 # i f d e f   S E Q U E N T I A L 
         s y s l o g ( L O G _ E M E R G ,   " [ T L S F ]   % d   m s   | |   f r e e :     ,   t o t a l :   % d   b y t e s " , 
         	 	 n o w _ t i m e   -   s t a r t _ t i m e ,   c M a l l o c S t a t i s t i c s _ g e t U s e d S i z e ( ) ) ; 
 # e n d i f 
         r e t u r n ; 
 } 
 
 / *   # [ < P O S T A M B L E > ] # 
   *       S0�0�0�0Nk0^椬SQ0鉙pe�0鴉M0~0Y0
   *   # [ < / P O S T A M B L E > ] # * / 
 
 # e n d i f   / *   t T L S F S t a t i s t i c s _ I N L I N E H   * / 
 