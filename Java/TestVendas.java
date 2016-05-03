
/**
 * Write a description of class Tests here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class TestVendas
{
    public static void main(String[] args){
        Venda v = new Venda("Y2252", "OT1519", 1, 49.79, 70, 6, 'N');
        Venda x = v.clone();
        v.setFilial(2);
        if(v.equals(x))
        	System.out.println("True");
        String tmp = v.toString();
        String tmp2 = x.toString();
        System.out.println(tmp);
        System.out.println(tmp2);
        

    }
}
