    struct Static_Initializer {
      Static_Initializer() {
	AIbase::register_class(new AIstruct());
      }
    };
    static Static_Initializer init;

    virtual AIbase* clone() {return new AIstruct();}

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)
    virtual string name() {return string(QUOTEME(NAMEPLAYER));}
//    virtual int color1() {return 0;}
//    virtual int color2() {return 0;}
//    virtual ~AIstruct() {}
