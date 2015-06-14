#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <glm/glm.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/list.hpp>
#include <tuple>
#include "MetaFunctions.hpp"

using mat4 = glm::mat4;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using texture2d = unsigned char;

template <class... DataType>
struct Data {
    using type = std::tuple<DataType...>;
    type value;
};

template <class Output>
struct Provider {
    using type = Output;
};

template <class input_list, class output_list>
struct Node {
    using input = input_list;
    using output = output_list;
};

template <class input_list, class output_list>
struct VertexShaderProgram {
    using input = input_list;
    using output = output_list;
};

template <class input_list, class output_list>
struct FragmentShaderProgram {
    using input = input_list;
    using output = output_list;
};

template <class VertexShaderProgram, class FragmentShaderProgram>
using ShaderProgram = Node<
    boost::mpl::push_back<boost::mpl::list<typename VertexShaderProgram::input>,
                          typename FragmentShaderProgram::input>,
    boost::mpl::push_back<
        boost::mpl::list<typename VertexShaderProgram::output>,
        typename FragmentShaderProgram::output>>;

#endif
