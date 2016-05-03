import java.io.Serializable;


/**
 * Write a description of class Venda here.
 * 
 * @author Grupo 18
 * @version (a version number or a date)
 */
public class Venda implements Serializable{
    //Variáveis de instancia
    private String cliente;
    private String produto;
    private int filial;
    private double preco;
    private int quantidade;
    private int mes;
    private char tipo;
    
    //Construtores
    
    public Venda() {
        cliente = "n/a";
        produto = "n/a";
        filial = -1;
        preco = 0.0;
        quantidade = 0;
        mes = -1;
        tipo = 'X';
    }
    
    public Venda(Venda v) {
        cliente = v.getCliente();
        produto = v.getProduto();
        filial = v.getFilial();
        preco = v.getPreco();
        quantidade = v.getQuantidade();
        mes = v.getMes();
        tipo = v.getTipo();
    }
    
    public Venda( String cliente, String produto, int filial, double preco, int quantidade, int mes, char tipo){
        this.cliente = cliente;
        this.produto = produto;
        this.filial = filial;
        this.preco = preco;
        this.quantidade = quantidade;
        this.mes = mes;
        this.tipo = tipo;
    }
    
    public String getCliente(){
        return cliente;
    }
    
    public String getProduto(){
        return produto;
    }
    
    public int getFilial(){
        return filial;
    }
    
    public double getPreco(){
        return preco;
    }
    
    public int getQuantidade(){
        return quantidade;
    }
    
    public int getMes(){
        return mes;
    }
    
    public char getTipo(){
        return tipo;
    }
    
    public void setCliente(String cliente){
        this.cliente = cliente;
    }
    
    public void setProduto(String produto){
        this.produto = produto;
    }
    
    public void setFilial(int filial){
        this.filial = filial;
    }
    
    public void setPreco(double preco){
        this.preco = preco;
    }
    
    public void setQuantidade(int quantidade){
        this.quantidade = quantidade;
    }
    
    public void setMes(int mes){
        this.mes = mes;
    }
    
    public void getTipo(char tipo){
        this.tipo = tipo;
    }
    
    public boolean equals(Object o){
        if(this == o)
            return true;
        if(o==null || this.getClass() != o.getClass())
            return false;
        Venda v = (Venda) o;
        if(this.cliente.equals(v.getCliente()) && this.produto.equals(v.getProduto())){
            if(this.filial == v.getFilial() && this.preco == v.getPreco()){
                if(this.quantidade == v.getQuantidade() && this.mes == v.getMes() && this.tipo == v.getTipo()){
                    return true;
                }
            }
        }
        return false;
    }
    
    public Venda clone(){
        return new Venda(this);
    }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(cliente); sb.append(" ");
        sb.append(produto); sb.append(" ");
        sb.append(filial); sb.append(" ");
        sb.append(preco); sb.append(" ");
        sb.append(quantidade); sb.append(" ");
        sb.append(mes); sb.append(" ");
        sb.append(tipo); sb.append("\n");
        return sb.toString();
    }
    
}
