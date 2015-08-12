
#include "Stickman.hpp"

StickmanModel StickmanModel::create(float neck_size, float arm_size, float body_size, float leg_size)
{
	constexpr const std::size_t nb_bones = 11;
	m_joints.resize(nb_bones);
	
	sf::Transform transform;
	
	// HEAD
	m_joints[0] = make_unique<GraphicsNode>(0.f, neck_size);
	// HANDS
	m_joints[1] = make_unique<GraphicsNode>(0.f, arm_size/2);
	m_joints[2] = make_unique<GraphicsNode>(0.f, arm_size/2);
	
	// ARMS
	m_joints[3] = make_unique<GraphicsNode>(pi/2, arm_size/2);
	m_joints[4] = make_unique<GraphicsNode>(-pi/2, arm_size/2);
	
	// NECK
	m_joints[5] = make_unique<GraphicsNode>(0.f, body_size, {3,4});
	
	// FEET
	m_joints[6] = make_unique<GraphicsNode>(0.f, leg_size/2);
	m_joints[7] = make_unique<GraphicsNode>(0.f, leg_size/2);
	
	// LEGS
	m_joints[8] = make_unique<GraphicsNode>(4*pi/3.f-pi/2, leg_size/2, {6});
	m_joints[9] = make_unique<GraphicsNode>(5*pi/3.f-pi/2, leg_size/2, {7});
	
	// BACK
	m_joints[10] = make_unique<GraphicsNode>(pi/2.f, leg_size, {5, 8, 9}); // Origin at feet
	
	m_mainJoint = GraphicsNode(0.f, 0.f, {10});
	
}

void StickmanModel::setRotation(std::size_t id, float rotation) {
	m_computed = false;
	m_joints.at(id)->transform.setRotation(rotation);
}

void StickmanModel::compute()
{
	if(!m_computed)
		computeNode(m_mainJoint, 0);
	m_computed = true;
}

void StickmanModel::computeNode(GraphicsNode& node, float angle)
{
	for (std::size_t child : node.children) {
		GraphicsNode& child_node = m_joints.at(child);
		float angle_tot = angle + child_node.angle;
		child_node.position = node.position + child_node.distanceFromParent * {std::cos(angle_tot), std::sin(angle_tot)};
		computeNode(child_node, angle_tot);
	}
}

const GraphicsNode& StickmanModel::getRootNode() const
{
	return m_mainJoint;
}


void StickmanView::setModel(const std::shared_ptr<StickmanModel> model) {
	m_model = std::move(model);
}

std::vector<float>&& StickmanView::getSquareDistanceFromPoint(const sf::Vector2f& point) {
	
	std::vector<float> dists;
	dists.resize(m_model->m_joints.size());
	auto iter_dist = dists.begin();
	auto iter_joint = m_model->m_joints->begin();
	for(;iter_joint != m_model->m_joints->end(); ++iter_joint) {
			auto vec = point - iter_joint->position;
			*iter_dist = vec.x*vec.x + vec.y*vec.y;
	}
	return dists;     
}

void StickmanView::render(sf::RenderTarget& target)
{
	m_model->compute();
	for(GraphicsNode* node : m_model->getRootNode().children)
		renderNode(target, *node);
}

void StickmanView::renderNode(sf::RenderTarget& target, const GraphicsNode& node, float angle)
{
	for(std::size_t child : node.children)
	{
		GraphicsNode& child_node = m_model->m_joints.at(child);
		sf::RectangleShape shape({1.f, child_node.distanceFromParent});
		shape.setPosition(node.position);
		shape.setRotation(angle + );
		target.draw(shape);
		renderNode(target, child_node);
	}
}

void StickmanController::setModel(StickmanModel& model)
{
	m_model = &model;
}

void StickmanController::setRigidGraphicsNodePosition(std::size_t node, const sf::Vector2f& position)
{
	// TODO
}

void StickmanController::setNodeToDirection(std::size_t node, const sf::Vector2f& direction)
{
	// TODO
}


void StickmanEditorView::highlightNode(std::size_t id, bool highlight)
{
	m_isHighlighted.at(id) = highlight;
}




