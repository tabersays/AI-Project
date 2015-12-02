#!/usr/bin/env ruby

#author Michael Taylor
#date November 30th 2015

puts "Name of node file?"
file_name = gets.gsub(/\s+/, "")
puts "How many input nodes?"
in_nodes = gets.to_i
puts "How many hidden nodes?"
hidden_nodes = gets.to_i
puts "Reduction step?"
reduction_step = gets.to_i


node = File.new(file_name, "w")
node.write("#{in_nodes}\n#{hidden_nodes}\n")

#first hidden layer conected to the input layer
for i in 0..hidden_nodes - 1
    node_data = "1"
    for j in 0..in_nodes - 1
        node_data = node_data + " " + rand(0.0...1.0).to_s
    end
    node_data = node_data + "@\n"
    node.write(node_data)
end
node.write("%\n")

#all other hidden layers
count = hidden_nodes/reduction_step
last_node_layer = 0
previous = hidden_nodes
puts "Node count =  #{count}."
while count > 1
    last_node_layer = count
    for i in 0..count - 1
        node_data = "1"
        for j in 0..previous - 1
             node_data = node_data + " " + rand(0.0...1.0).to_s
        end
        node_data = node_data + "@\n"
        node.write(node_data)
    end
    previous = count
    node.write("%\n")
    count = (count / reduction_step).floor
    puts "Node count =  #{count}."
end

if last_node_layer != 1
    node_data = "1"
    for i in 0..last_node_layer - 1
        node_data = node_data + " " + rand(0.0...1.0).to_s
    end
    node_data = node_data + "@\n"
    node.write(node_data)
    node.write("%\n")
end
